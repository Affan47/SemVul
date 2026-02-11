clear_limitv(
rspl *s
) {
	int i;
	float *gp;

	if (s->g.limitv_cached != 0) {

		for (i = 0, gp = s->g.a; i < s->g.no; i++, gp += s->g.pss) {
			gp[-1] = L_UNINIT;
		}
		s->g.limitv_cached = 0;
	}
}
