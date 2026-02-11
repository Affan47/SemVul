sample_move_dither_shaped_d16_sS (char *dst,  jack_default_audio_sample_t *src, unsigned long nsamples, unsigned long dst_skip, dither_state_t *state)
{
	jack_default_audio_sample_t     x;
	jack_default_audio_sample_t     xe;
	jack_default_audio_sample_t     xp;
	float        r;
	float        rm1 = state->rm1;
	unsigned int idx = state->idx;

	while (nsamples--) {
		x = *src * SAMPLE_16BIT_SCALING;
		r = ((float)fast_rand() + (float)fast_rand()) / (float)UINT_MAX - 1.0f;


		xe = x
		     - state->e[idx] * 2.033f
		     + state->e[(idx - 1) & DITHER_BUF_MASK] * 2.165f
		     - state->e[(idx - 2) & DITHER_BUF_MASK] * 1.959f
		     + state->e[(idx - 3) & DITHER_BUF_MASK] * 1.590f
		     - state->e[(idx - 4) & DITHER_BUF_MASK] * 0.6149f;
		xp = xe + r - rm1;
		rm1 = r;

		float_16_scaled (xp, *((int16_t*) dst));


		idx = (idx + 1) & DITHER_BUF_MASK;
		state->e[idx] = *((int16_t*) dst) - xe;

		dst += dst_skip;
		src++;
	}
	state->rm1 = rm1;
	state->idx = idx;
}
