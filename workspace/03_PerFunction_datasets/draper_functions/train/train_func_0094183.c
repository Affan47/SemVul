apply_pitch_modifications(DUMB_IT_SIGDATA *sigdata, IT_PLAYING *playing, float *delta, int *cutoff)
{
	{
		int sample_vibrato_shift = it_sine[playing->sample_vibrato_time];

		if (sigdata->flags & IT_WAS_AN_XM) {
			int depth = playing->sample->vibrato_depth;
			if (playing->sample->vibrato_rate) {
				depth *= playing->sample_vibrato_depth;
				depth /= playing->sample->vibrato_rate;
			}
			sample_vibrato_shift *= depth;
		} else
			sample_vibrato_shift *= playing->sample_vibrato_depth >> 8;

		sample_vibrato_shift >>= 4;

		*delta *= (float)pow(DUMB_PITCH_BASE, sample_vibrato_shift);
	}

	if (playing->env_instrument &&
		(playing->env_instrument->pitch_envelope.flags & IT_ENVELOPE_ON))
	{
		int p = envelope_get_y(&playing->env_instrument->pitch_envelope, &playing->pitch_envelope);
		if (playing->env_instrument->pitch_envelope.flags & IT_ENVELOPE_PITCH_IS_FILTER)
			*cutoff = (*cutoff * (p+(32<<IT_ENVELOPE_SHIFT))) >> (6 + IT_ENVELOPE_SHIFT);
		else
			*delta *= (float)pow(DUMB_PITCH_BASE, p >> (IT_ENVELOPE_SHIFT - 7));
	}
}
