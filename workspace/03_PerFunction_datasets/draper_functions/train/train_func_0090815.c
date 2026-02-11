xcal_interp_ch(xcal *p, int ch, double in) {
	co tp;

	if (ch < 0 || ch >= p->devchan)
		return -1.0;

	tp.p[0] = in;
	p->cals[ch]->interp(p->cals[ch], &tp);
	return tp.v[0];
}
