ast_mf_detect_init (mf_detect_state_t *s, unsigned int sample_rate)
{
	int i;
	s->hits[0] = s->hits[1] = s->hits[2] = s->hits[3] = s->hits[4] = 0;
	for (i = 0;  i < 6;  i++) {
		goertzel_init (&s->tone_out[i], mf_tones[i], MF_GSIZE, sample_rate);
	}
	s->current_sample = 0;
	s->current_hit = 0;
}
