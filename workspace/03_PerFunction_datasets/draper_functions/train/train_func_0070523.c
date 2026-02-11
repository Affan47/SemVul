v_bignum_mod(VBigDig *x, const VBigDig *y)
{
	int	digs;
	VBigDig	*tmp;


	digs = *x > *y ? *x : *y;
	tmp = bignum_alloc(digs);
	v_bignum_div(x, y, tmp);
	v_bignum_set_bignum(x, tmp);
	bignum_free(tmp);


}
