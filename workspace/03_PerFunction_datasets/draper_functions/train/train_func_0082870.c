exp_var(NumericVar *arg, NumericVar *result, int rscale)
{
	NumericVar	x;
	int			xintval;
	bool		xneg = FALSE;
	int			local_rscale;


	init_var(&x);

	set_var_from_var(arg, &x);

	if (x.sign == NUMERIC_NEG)
	{
		xneg = TRUE;
		x.sign = NUMERIC_POS;
	}


	xintval = 0;
	while (x.weight >= 0)
	{
		xintval *= NBASE;
		if (x.ndigits > 0)
		{
			xintval += x.digits[0];
			x.digits++;
			x.ndigits--;
		}
		x.weight--;

		if (xintval >= NUMERIC_MAX_RESULT_SCALE * 3)
			ereport(ERROR,
					(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
					 errmsg("argument for function \"exp\" too big")));
	}


	local_rscale = rscale + MUL_GUARD_DIGITS * 2;


	exp_var_internal(&x, result, local_rscale);


	if (xintval > 0)
	{
		NumericVar	e;

		init_var(&e);
		exp_var_internal(&const_one, &e, local_rscale);
		power_var_int(&e, xintval, &e, local_rscale);
		mul_var(&e, result, result, local_rscale);
		free_var(&e);
	}


	if (xneg)
		div_var(&const_one, result, result, rscale, true);
	else
		round_var(result, rscale);

	free_var(&x);
}
