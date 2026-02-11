interval2tm(Interval span, struct pg_tm * tm, fsec_t *fsec)
{
#ifdef HAVE_INT64_TIMESTAMP
	int64		time;
	int64		tfrac;
#else
	double		time;
	double		tfrac;
#endif

	tm->tm_year = span.month / MONTHS_PER_YEAR;
	tm->tm_mon = span.month % MONTHS_PER_YEAR;
	tm->tm_mday = span.day;
	time = span.time;

#ifdef HAVE_INT64_TIMESTAMP
	tfrac = time / USECS_PER_HOUR;
	time -= tfrac * USECS_PER_HOUR;
	tm->tm_hour = tfrac;
	tfrac = time / USECS_PER_MINUTE;
	time -= tfrac * USECS_PER_MINUTE;
	tm->tm_min = tfrac;
	tfrac = time / USECS_PER_SEC;
	*fsec = time - (tfrac * USECS_PER_SEC);
	tm->tm_sec = tfrac;
#else
recalc:
	TMODULO(time, tfrac, (double) SECS_PER_HOUR);
	tm->tm_hour = tfrac;
	TMODULO(time, tfrac, (double) SECS_PER_MINUTE);
	tm->tm_min = tfrac;
	TMODULO(time, tfrac, 1.0);
	tm->tm_sec = tfrac;
	time = TSROUND(time);

	if (time >= 1.0)
	{
		time = ceil(span.time);
		goto recalc;
	}
	*fsec = time;
#endif

	return 0;
}
