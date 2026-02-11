__frexp_exp(double x, int *expt)
{
	double exp_x;
	u_int32_t hx;


	exp_x = exp(x - kln2);
	GET_HIGH_WORD(hx, exp_x);
	*expt = (hx >> 20) - (0x3ff + 1023) + k;
	SET_HIGH_WORD(exp_x, (hx & 0xfffff) | ((0x3ff + 1023) << 20));
	return (exp_x);
}
