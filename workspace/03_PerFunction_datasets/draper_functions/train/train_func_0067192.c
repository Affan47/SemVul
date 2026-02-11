v_bignum_set_bignum(VBigDig *x, const VBigDig *y)
{
	int	xs, ys, i, s;

	xs = x[0];
	ys = y[0];
	if(xs == ys)
	{
		memcpy(x + 1, y + 1, xs * sizeof *x);
		return;
	}
	else if(ys > xs)
		s = xs;
	else
		s = ys;

	for(i = 1; i <= s; i++)
		x[i] = y[i];
	for(; i <= xs; i++)
		x[i] = 0;
}
