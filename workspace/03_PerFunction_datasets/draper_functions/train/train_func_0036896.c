icmNamedColor_allocate(
	icmBase *pp
) {
	icmNamedColor *p = (icmNamedColor *)pp;
	icc *icp = p->icp;

	if (p->count != p->_count) {
		unsigned int i;
		if (ovr_mul(p->count, sizeof(icmNamedColorVal))) {
			sprintf(icp->err,"icmNamedColor_alloc: size overflow");
			return icp->errc = 1;
		}
		if (p->data != NULL)
			icp->al->free(icp->al, p->data);
		if ((p->data = (icmNamedColorVal *) icp->al->calloc(icp->al,p->count, sizeof(icmNamedColorVal))) == NULL) {
			sprintf(icp->err,"icmNamedColor_alloc: malloc() of icmNamedColor data failed");
			return icp->errc = 2;
		}
		for (i = 0; i < p->count; i++) {
			p->data[i].icp = icp;
		}
		p->_count = p->count;
	}
	return 0;
}
