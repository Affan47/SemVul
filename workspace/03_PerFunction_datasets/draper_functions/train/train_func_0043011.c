numeric_exp(PG_FUNCTION_ARGS)
{
	Numeric		num = PG_GETARG_NUMERIC(0);
	Numeric		res;
	NumericVar	arg;
	NumericVar	result;
	int			rscale;
	double		val;


	if (NUMERIC_IS_NAN(num))
		PG_RETURN_NUMERIC(make_result(&const_nan));


	init_var(&arg);
	init_var(&result);

	set_var_from_num(num, &arg);


	val = numericvar_to_double_no_overflow(&arg);


	val *= 0.434294481903252;


	val = Max(val, -NUMERIC_MAX_RESULT_SCALE);
	val = Min(val, NUMERIC_MAX_RESULT_SCALE);

	rscale = NUMERIC_MIN_SIG_DIGITS - (int) val;
	rscale = Max(rscale, arg.dscale);
	rscale = Max(rscale, NUMERIC_MIN_DISPLAY_SCALE);
	rscale = Min(rscale, NUMERIC_MAX_DISPLAY_SCALE);


	exp_var(&arg, &result, rscale);

	res = make_result(&result);

	free_var(&result);
	free_var(&arg);

	PG_RETURN_NUMERIC(res);
}
