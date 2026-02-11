add_big(bignum_t *x, bignum_t *y, bignum_t *z)
{
	int xl, yl, k, i;
	uint64 *xp, *yp, *zp;

	safety_assert(x->l < BIGSIZE);
	safety_assert(x->l >= 0);
	safety_assert(y->l < BIGSIZE);
	safety_assert(y->l >= 0);

	xl = x->l;
	yl = y->l;
	if (yl > xl) {
		int tl;
		bignum_t *tn;
		tl = xl; xl = yl; yl = tl;
		tn = x; x = y; y = tn;
	}

	xp = &x->d[0];
	yp = &y->d[0];
	zp = &z->d[0];

	for (i = yl, k = 0; i >= 0; i--)
		ADD(*xp++, *yp++, *zp++, k);
	for (i = xl-yl; k && i > 0; i--) {
		uint64 z_add;
		z_add = *xp++ + 1;
		k = (z_add == 0);
		*zp++ = z_add;
	}
	for (; i > 0; i--)
		*zp++ = *xp++;
	if (k)
		*zp = 1, z->l = xl+1;
	else
		z->l = xl;
	safety_assert(z->l < BIGSIZE);
	safety_assert(z->l >= 0);
}
