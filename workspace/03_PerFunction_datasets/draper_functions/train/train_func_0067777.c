reltime_interval(PG_FUNCTION_ARGS)
{
	RelativeTime reltime = PG_GETARG_RELATIVETIME(0);
	Interval   *result;
	int			year,
				month,
				day;

	result = (Interval *) palloc(sizeof(Interval));

	switch (reltime)
	{
		case INVALID_RELTIME:
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				  errmsg("cannot convert reltime \"invalid\" to interval")));
			result->time = 0;
			result->day = 0;
			result->month = 0;
			break;

		default:
#ifdef HAVE_INT64_TIMESTAMP
			year = reltime / SECS_PER_YEAR;
			reltime -= year * SECS_PER_YEAR;
			month = reltime / (DAYS_PER_MONTH * SECS_PER_DAY);
			reltime -= month * (DAYS_PER_MONTH * SECS_PER_DAY);
			day = reltime / SECS_PER_DAY;
			reltime -= day * SECS_PER_DAY;

			result->time = (reltime * USECS_PER_SEC);
#else
			TMODULO(reltime, year, SECS_PER_YEAR);
			TMODULO(reltime, month, DAYS_PER_MONTH * SECS_PER_DAY);
			TMODULO(reltime, day, SECS_PER_DAY);

			result->time = reltime;
#endif
			result->month = MONTHS_PER_YEAR * year + month;
			result->day = day;
			break;
	}

	PG_RETURN_INTERVAL_P(result);
}
