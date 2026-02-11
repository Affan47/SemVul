elem_lt(elem_t x, elem_t y)
{
	if (x.key < y.key) return 1;
	if (x.key == y.key) {
		int t;
		t = strcmp(bam_get_qname(x.b), bam_get_qname(y.b));
		if (t < 0) return 1;
		return (t == 0 && ((x.b->core.flag>>6&3) < (y.b->core.flag>>6&3)));
	} else return 0;
}
