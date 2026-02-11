dlog1(PG_FUNCTION_ARGS)
{
	float8		arg1 = PG_GETARG_FLOAT8(0);
	float8		result;


	if (arg1 == 0.0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_ARGUMENT_FOR_LOG),
				 errmsg("cannot take logarithm of zero")));
	if (arg1 < 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_ARGUMENT_FOR_LOG),
				 errmsg("cannot take logarithm of a negative number")));

	result = log(arg1);

	CHECKFLOATVAL(result, isinf(arg1), arg1 == 1);
	PG_RETURN_FLOAT8(result);
}
