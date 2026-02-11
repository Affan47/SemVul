iter_end(cdb *c) {
	if (c->end != 0) {
		c->end = 0;
		SvREFCNT_dec(c->curkey);
	}
}
