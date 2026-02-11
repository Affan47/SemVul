cookedtoraw(alphix *p, int ix) {
	int i;

	if (p->nr == 0)
		return ix;

	for (i = 0; i < p->nr; i++) {
		if (ix >= p->rs[i].c0 && ix <= p->rs[i].c1) {
			ix = ix - p->rs[i].c0 + p->rs[i].r0;
			return ix;
		}
	}
	return -1;
}
