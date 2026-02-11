get_next_touch(
rspl *s
) {
	unsigned int tg;
	float *gp,*ep;

	if ((tg = ++s->g.touch) == 0) {


		for (gp = s->g.a, ep = s->g.a + s->g.no * s->g.pss; gp < ep; gp += s->g.pss) {
			TOUCHF(gp) = 0;
		}
		tg = ++s->g.touch;
	}
	return tg;
}
