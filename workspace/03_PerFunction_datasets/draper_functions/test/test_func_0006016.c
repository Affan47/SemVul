timetz_recv(PG_FUNCTION_ARGS)
{
	StringInfo	buf = (StringInfo) PG_GETARG_POINTER(0);

#ifdef NOT_USED
	Oid			typelem = PG_GETARG_OID(1);
#endif
	int32		typmod = PG_GETARG_INT32(2);
	TimeTzADT  *result;

	result = (TimeTzADT *) palloc(sizeof(TimeTzADT));

#ifdef HAVE_INT64_TIMESTAMP
	result->time = pq_getmsgint64(buf);

	if (result->time < INT64CONST(0) || result->time > USECS_PER_DAY)
		ereport(ERROR,
				(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
				 errmsg("time out of range")));
#else
	result->time = pq_getmsgfloat8(buf);

	if (result->time < 0 || result->time > (double) SECS_PER_DAY)
		ereport(ERROR,
				(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
				 errmsg("time out of range")));
#endif

	result->zone = pq_getmsgint(buf, sizeof(result->zone));


	if (result->zone <= -15 * SECS_PER_HOUR ||
		result->zone >= 15 * SECS_PER_HOUR)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TIME_ZONE_DISPLACEMENT_VALUE),
				 errmsg("time zone displacement out of range")));

	AdjustTimeForTypmod(&(result->time), typmod);

	PG_RETURN_TIMETZADT_P(result);
}
