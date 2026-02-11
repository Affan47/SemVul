timenow(PG_FUNCTION_ARGS)
{
	time_t		sec;

	if (time(&sec) < 0)
		PG_RETURN_ABSOLUTETIME(INVALID_ABSTIME);

	PG_RETURN_ABSOLUTETIME((AbsoluteTime) sec);
}
