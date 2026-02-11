exp_var_internal(NumericVar *arg, NumericVar *result, int rscale)
{
	NumericVar	x;
	NumericVar	xpow;
	NumericVar	ifac;
	NumericVar	elem;
	NumericVar	ni;
	int			ndiv2 = 0;
	int			local_rscale;

	init_var(&x);
	init_var(&xpow);
	init_var(&ifac);
	init_var(&elem);
	init_var(&ni);

	set_var_from_var(arg, &x);

	Assert(x.sign == NUMERIC_POS);

	local_rscale = rscale + 8;


	while (cmp_var(&x, &const_zero_point_01) > 0)
	{
		ndiv2++;
		local_rscale++;
		mul_var(&x, &const_zero_point_five, &x, x.dscale + 1);
	}


	add_var(&const_one, &x, result);
	set_var_from_var(&x, &xpow);
	set_var_from_var(&const_one, &ifac);
	set_var_from_var(&const_one, &ni);

	for (;;)
	{
		add_var(&ni, &const_one, &ni);
		mul_var(&xpow, &x, &xpow, local_rscale);
		mul_var(&ifac, &ni, &ifac, 0);
		div_var(&xpow, &ifac, &elem, local_rscale, true);

		if (elem.ndigits == 0)
			break;

		add_var(result, &elem, result);
	}


	while (ndiv2-- > 0)
		mul_var(result, result, result, local_rscale);

	free_var(&x);
	free_var(&xpow);
	free_var(&ifac);
	free_var(&elem);
	free_var(&ni);
}
