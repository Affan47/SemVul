numeric_int8(PG_FUNCTION_ARGS)
{
	Numeric		num = PG_GETARG_NUMERIC(0);
	NumericVar	x;
	int64		result;


	if (NUMERIC_IS_NAN(num))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot convert NaN to bigint")));


	init_var(&x);
	set_var_from_num(num, &x);

	if (!numericvar_to_int8(&x, &result))
		ereport(ERROR,
				(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
				 errmsg("bigint out of range")));

	free_var(&x);

	PG_RETURN_INT64(result);
}
