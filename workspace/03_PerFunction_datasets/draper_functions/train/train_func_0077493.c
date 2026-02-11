numeric_power(PG_FUNCTION_ARGS)
{
	Numeric		num1 = PG_GETARG_NUMERIC(0);
	Numeric		num2 = PG_GETARG_NUMERIC(1);
	Numeric		res;
	NumericVar	arg1;
	NumericVar	arg2;
	NumericVar	arg2_trunc;
	NumericVar	result;


	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		PG_RETURN_NUMERIC(make_result(&const_nan));


	init_var(&arg1);
	init_var(&arg2);
	init_var(&arg2_trunc);
	init_var(&result);

	set_var_from_num(num1, &arg1);
	set_var_from_num(num2, &arg2);
	set_var_from_var(&arg2, &arg2_trunc);

	trunc_var(&arg2_trunc, 0);


	if ((cmp_var(&arg1, &const_zero) == 0 &&
		 cmp_var(&arg2, &const_zero) < 0) ||
		(cmp_var(&arg1, &const_zero) < 0 &&
		 cmp_var(&arg2, &arg2_trunc) != 0))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_ARGUMENT_FOR_POWER_FUNCTION),
				 errmsg("invalid argument for power function")));


	power_var(&arg1, &arg2, &result);

	res = make_result(&result);

	free_var(&result);
	free_var(&arg2);
	free_var(&arg2_trunc);
	free_var(&arg1);

	PG_RETURN_NUMERIC(res);
}
