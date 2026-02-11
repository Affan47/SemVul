afsk48p_init(struct demod_state *s)
{
	float f;
	int i;

	pprz_init(s);
	memset(&s->l1.afsk48p, 0, sizeof(s->l1.afsk48p));
	for (f = 0, i = 0; i < CORRLEN; i++) {
		corr_mark_i[i] = cos(f);
		corr_mark_q[i] = sin(f);
		f += 2.0*M_PI*FREQ_MARK/FREQ_SAMP;
	}
	for (f = 0, i = 0; i < CORRLEN; i++) {
		corr_space_i[i] = cos(f);
		corr_space_q[i] = sin(f);
		f += 2.0*M_PI*FREQ_SPACE/FREQ_SAMP;
	}
	for (i = 0; i < CORRLEN; i++) {
		f = 0.54 - 0.46*cos(2*M_PI*i/(float)(CORRLEN-1));
		corr_mark_i[i] *= f;
		corr_mark_q[i] *= f;
		corr_space_i[i] *= f;
		corr_space_q[i] *= f;
	}

	s->l1.afsk48p.sample_count = 0;
}
