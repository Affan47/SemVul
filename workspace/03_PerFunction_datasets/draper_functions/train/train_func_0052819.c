rdata_order(const void *av, const void *bv) {
	dns_difftuple_t const * const *ap = av;
	dns_difftuple_t const * const *bp = bv;
	dns_difftuple_t const *a = *ap;
	dns_difftuple_t const *b = *bp;
	int r;
	r = (b->rdata.type - a->rdata.type);
	if (r != 0)
		return (r);
	r = dns_rdata_compare(&a->rdata, &b->rdata);
	return (r);
}
