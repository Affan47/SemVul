interval_part(PG_FUNCTION_ARGS)
{
	text	   *units = PG_GETARG_TEXT_PP(0);
	Interval   *interval = PG_GETARG_INTERVAL_P(1);
	float8		result;
	int			type,
				val;
	char	   *lowunits;
	fsec_t		fsec;
	struct pg_tm tt,
			   *tm = &tt;

	lowunits = downcase_truncate_identifier(VARDATA_ANY(units),
											VARSIZE_ANY_EXHDR(units),
											false);

	type = DecodeUnits(0, lowunits, &val);
	if (type == UNKNOWN_FIELD)
		type = DecodeSpecial(0, lowunits, &val);

	if (type == UNITS)
	{
		if (interval2tm(*interval, tm, &fsec) == 0)
		{
			switch (val)
			{
				case DTK_MICROSEC:
#ifdef HAVE_INT64_TIMESTAMP
					result = tm->tm_sec * 1000000.0 + fsec;
#else
					result = (tm->tm_sec + fsec) * 1000000;
#endif
					break;

				case DTK_MILLISEC:
#ifdef HAVE_INT64_TIMESTAMP
					result = tm->tm_sec * 1000.0 + fsec / 1000.0;
#else
					result = (tm->tm_sec + fsec) * 1000;
#endif
					break;

				case DTK_SECOND:
#ifdef HAVE_INT64_TIMESTAMP
					result = tm->tm_sec + fsec / 1000000.0;
#else
					result = tm->tm_sec + fsec;
#endif
					break;

				case DTK_MINUTE:
					result = tm->tm_min;
					break;

				case DTK_HOUR:
					result = tm->tm_hour;
					break;

				case DTK_DAY:
					result = tm->tm_mday;
					break;

				case DTK_MONTH:
					result = tm->tm_mon;
					break;

				case DTK_QUARTER:
					result = (tm->tm_mon / 3) + 1;
					break;

				case DTK_YEAR:
					result = tm->tm_year;
					break;

				case DTK_DECADE:

					result = tm->tm_year / 10;
					break;

				case DTK_CENTURY:

					result = tm->tm_year / 100;
					break;

				case DTK_MILLENNIUM:

					result = tm->tm_year / 1000;
					break;

				default:
					ereport(ERROR,
							(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							 errmsg("interval units \"%s\" not supported",
									lowunits)));
					result = 0;
			}

		}
		else
		{
			elog(ERROR, "could not convert interval to tm");
			result = 0;
		}
	}
	else if (type == RESERV && val == DTK_EPOCH)
	{
#ifdef HAVE_INT64_TIMESTAMP
		result = interval->time / 1000000.0;
#else
		result = interval->time;
#endif
		result += ((double) DAYS_PER_YEAR * SECS_PER_DAY) * (interval->month / MONTHS_PER_YEAR);
		result += ((double) DAYS_PER_MONTH * SECS_PER_DAY) * (interval->month % MONTHS_PER_YEAR);
		result += ((double) SECS_PER_DAY) * interval->day;
	}
	else
	{
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("interval units \"%s\" not recognized",
						lowunits)));
		result = 0;
	}

	PG_RETURN_FLOAT8(result);
}
