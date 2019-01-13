/* Copyright (c) 2017-2018 Mozilla */
/*
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "kiss_fft.h"

#define PREEMPHASIS (0.85f)

#define FRAME_SIZE_5MS (2)
#define OVERLAP_SIZE_5MS (2)
#define TRAINING_OFFSET_5MS (1)

#define WINDOW_SIZE_5MS (FRAME_SIZE_5MS + OVERLAP_SIZE_5MS)

#define FRAME_SIZE (80*FRAME_SIZE_5MS)
#define OVERLAP_SIZE (80*OVERLAP_SIZE_5MS)
#define TRAINING_OFFSET (80*TRAINING_OFFSET_5MS)
#define WINDOW_SIZE (FRAME_SIZE + OVERLAP_SIZE)
#define FREQ_SIZE (WINDOW_SIZE/2 + 1)

#define NB_BANDS 18

void lpc_to_lsp(float *a, int order, float *freq);
void lsp_to_lpc(float *lsp, float *ak, int order);

void compute_band_energy_from_lpc(float *bandE, const kiss_fft_cpx *X);
void compute_band_energy(float *bandE, const kiss_fft_cpx *X);
void compute_band_corr(float *bandE, const kiss_fft_cpx *X, const kiss_fft_cpx *P);

void apply_window(float *x);
void dct(float *out, const float *in);
void idct(float *out, const float *in);
void forward_transform(kiss_fft_cpx *out, const float *in);
void inverse_transform(float *out, const kiss_fft_cpx *in);
float lpc_from_bands(float *lpc, const float *Ex);
float lpc_from_cepstrum(float *lpc, const float *cepstrum);
void apply_window(float *x);

