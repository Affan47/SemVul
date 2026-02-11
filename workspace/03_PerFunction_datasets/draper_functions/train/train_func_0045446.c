power_var(NumericVar *base, NumericVar *exp, NumericVar *result)
{
	NumericVar	ln_base;
	NumericVar	ln_num;
	int			dec_digits;
	int			rscale;
	int			local_rscale;
	double		val;


	if (exp->ndigits == 0 || exp->ndigits <= exp->weight + 1)
	{

		NumericVar	x;
		int64		expval64;


		init_var(&x);
		set_var_from_var(exp, &x);
		if (numericvar_to_int8(&x, &expval64))
		{
			int			expval = (int) expval64;


			if ((int64) expval == expval64)
			{

				rscale = NUMERIC_MIN_SIG_DIGITS;
				rscale = Max(rscale, base->dscale);
				rscale = Max(rscale, NUMERIC_MIN_DISPLAY_SCALE);
				rscale = Min(rscale, NUMERIC_MAX_DISPLAY_SCALE);

				power_var_int(base, expval, result, rscale);

				free_var(&x);
				return;
			}
		}
		free_var(&x);
	}

	init_var(&ln_base);
	init_var(&ln_num);


	dec_digits = (base->weight + 1) * DEC_DIGITS;

	if (dec_digits > 1)
		rscale = NUMERIC_MIN_SIG_DIGITS * 2 - (int) log10(dec_digits - 1);
	else if (dec_digits < 1)
		rscale = NUMERIC_MIN_SIG_DIGITS * 2 - (int) log10(1 - dec_digits);
	else
		rscale = NUMERIC_MIN_SIG_DIGITS * 2;

	rscale = Max(rscale, base->dscale * 2);
	rscale = Max(rscale, exp->dscale * 2);
	rscale = Max(rscale, NUMERIC_MIN_DISPLAY_SCALE * 2);
	rscale = Min(rscale, NUMERIC_MAX_DISPLAY_SCALE * 2);

	local_rscale = rscale + 8;

	ln_var(base, &ln_base, local_rscale);

	mul_var(&ln_base, exp, &ln_num, local_rscale);


	val = numericvar_to_double_no_overflow(&ln_num);


	val *= 0.434294481903252;


	val = Max(val, -NUMERIC_MAX_RESULT_SCALE);
	val = Min(val, NUMERIC_MAX_RESULT_SCALE);

	rscale = NUMERIC_MIN_SIG_DIGITS - (int) val;
	rscale = Max(rscale, base->dscale);
	rscale = Max(rscale, exp->dscale);
	rscale = Max(rscale, NUMERIC_MIN_DISPLAY_SCALE);
	rscale = Min(rscale, NUMERIC_MAX_DISPLAY_SCALE);

	exp_var(&ln_num, result, rscale);

	free_var(&ln_num);
	free_var(&ln_base);
}
