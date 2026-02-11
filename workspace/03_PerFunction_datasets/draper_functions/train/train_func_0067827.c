timetz_part(PG_FUNCTION_ARGS)
{
	text	   *units = PG_GETARG_TEXT_PP(0);
	TimeTzADT  *time = PG_GETARG_TIMETZADT_P(1);
	float8		result;
	int			type,
				val;
	char	   *lowunits;

	lowunits = downcase_truncate_identifier(VARDATA_ANY(units),
											VARSIZE_ANY_EXHDR(units),
											false);

	type = DecodeUnits(0, lowunits, &val);
	if (type == UNKNOWN_FIELD)
		type = DecodeSpecial(0, lowunits, &val);

	if (type == UNITS)
	{
		double		dummy;
		int			tz;
		fsec_t		fsec;
		struct pg_tm tt,
				   *tm = &tt;

		timetz2tm(time, tm, &fsec, &tz);

		switch (val)
		{
			case DTK_TZ:
				result = -tz;
				break;

			case DTK_TZ_MINUTE:
				result = -tz;
				result /= SECS_PER_MINUTE;
				FMODULO(result, dummy, (double) SECS_PER_MINUTE);
				break;

			case DTK_TZ_HOUR:
				dummy = -tz;
				FMODULO(dummy, result, (double) SECS_PER_HOUR);
				break;

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
			case DTK_MONTH:
			case DTK_QUARTER:
			case DTK_YEAR:
			case DTK_DECADE:
			case DTK_CENTURY:
			case DTK_MILLENNIUM:
			default:
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				errmsg("\"time with time zone\" units \"%s\" not recognized",
					   lowunits)));
				result = 0;
		}
	}
	else if (type == RESERV && val == DTK_EPOCH)
	{
#ifdef HAVE_INT64_TIMESTAMP
		result = time->time / 1000000.0 + time->zone;
#else
		result = time->time + time->zone;
#endif
	}
	else
	{
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("\"time with time zone\" units \"%s\" not recognized",
						lowunits)));
		result = 0;
	}

	PG_RETURN_FLOAT8(result);
}
