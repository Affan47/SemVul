numeric_sqrt(PG_FUNCTION_ARGS)
{
	Numeric		num = PG_GETARG_NUMERIC(0);
	Numeric		res;
	NumericVar	arg;
	NumericVar	result;
	int			sweight;
	int			rscale;


	if (NUMERIC_IS_NAN(num))
		PG_RETURN_NUMERIC(make_result(&const_nan));


	init_var(&arg);
	init_var(&result);

	set_var_from_num(num, &arg);


	sweight = (arg.weight + 1) * DEC_DIGITS / 2 - 1;

	rscale = NUMERIC_MIN_SIG_DIGITS - sweight;
	rscale = Max(rscale, arg.dscale);
	rscale = Max(rscale, NUMERIC_MIN_DISPLAY_SCALE);
	rscale = Min(rscale, NUMERIC_MAX_DISPLAY_SCALE);


	sqrt_var(&arg, &result, rscale);

	res = make_result(&result);

	free_var(&result);
	free_var(&arg);

	PG_RETURN_NUMERIC(res);
}
