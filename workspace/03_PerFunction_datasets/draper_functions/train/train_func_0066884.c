numeric_div(PG_FUNCTION_ARGS)
{
	Numeric		num1 = PG_GETARG_NUMERIC(0);
	Numeric		num2 = PG_GETARG_NUMERIC(1);
	NumericVar	arg1;
	NumericVar	arg2;
	NumericVar	result;
	Numeric		res;
	int			rscale;


	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		PG_RETURN_NUMERIC(make_result(&const_nan));


	init_var(&arg1);
	init_var(&arg2);
	init_var(&result);

	set_var_from_num(num1, &arg1);
	set_var_from_num(num2, &arg2);


	rscale = select_div_scale(&arg1, &arg2);


	div_var(&arg1, &arg2, &result, rscale, true);

	res = make_result(&result);

	free_var(&arg1);
	free_var(&arg2);
	free_var(&result);

	PG_RETURN_NUMERIC(res);
}
