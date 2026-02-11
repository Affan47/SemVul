timestamp_finite(PG_FUNCTION_ARGS)
{
	Timestamp	timestamp = PG_GETARG_TIMESTAMP(0);

	PG_RETURN_BOOL(!TIMESTAMP_NOT_FINITE(timestamp));
}
