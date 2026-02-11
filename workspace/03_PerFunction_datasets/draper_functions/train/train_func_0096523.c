bn_lshift(bignum256 *a)
{
	int i;
	for (i = 8; i > 0; i--) {
		a->val[i] = ((a->val[i] << 1) & 0x3FFFFFFF) | ((a->val[i - 1] & 0x20000000) >> 29);
	}
	a->val[0] = (a->val[0] << 1) & 0x3FFFFFFF;
}
