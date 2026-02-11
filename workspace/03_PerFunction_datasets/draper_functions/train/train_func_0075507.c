intinterval(PG_FUNCTION_ARGS)
{
	AbsoluteTime t = PG_GETARG_ABSOLUTETIME(0);
	TimeInterval tinterval = PG_GETARG_TIMEINTERVAL(1);

	if (tinterval->status == T_INTERVAL_VALID && t != INVALID_ABSTIME)
	{
		if (DatumGetBool(DirectFunctionCall2(abstimege,
											 AbsoluteTimeGetDatum(t),
								AbsoluteTimeGetDatum(tinterval->data[0]))) &&
			DatumGetBool(DirectFunctionCall2(abstimele,
											 AbsoluteTimeGetDatum(t),
								  AbsoluteTimeGetDatum(tinterval->data[1]))))
			PG_RETURN_BOOL(true);
	}
	PG_RETURN_BOOL(false);
}
