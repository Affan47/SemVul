numeric_log(PG_FUNCTION_ARGS)
{
	Numeric		num1 = PG_GETARG_NUMERIC(0);
	Numeric		num2 = PG_GETARG_NUMERIC(1);
	Numeric		res;
	NumericVar	arg1;
	NumericVar	arg2;
	NumericVar	result;


	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		PG_RETURN_NUMERIC(make_result(&const_nan));


	init_var_from_num(num1, &arg1);
	init_var_from_num(num2, &arg2);
	init_var(&result);


	log_var(&arg1, &arg2, &result);

	res = make_result(&result);

	free_var(&result);

	PG_RETURN_NUMERIC(res);
}
