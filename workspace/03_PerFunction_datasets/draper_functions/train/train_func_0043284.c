time_part(PG_FUNCTION_ARGS)
{
	text	   *units = PG_GETARG_TEXT_P(0);
	TimeADT		time = PG_GETARG_TIMEADT(1);
	float8		result;
	int			type,
				val;
	char	   *lowunits;

	lowunits = downcase_truncate_identifier(VARDATA(units),
											VARSIZE(units) - VARHDRSZ,
											false);

	type = DecodeUnits(0, lowunits, &val);
	if (type == UNKNOWN_FIELD)
		type = DecodeSpecial(0, lowunits, &val);

	if (type == UNITS)
	{
		fsec_t		fsec;
		struct pg_tm tt,
				   *tm = &tt;

		time2tm(time, tm, &fsec);

		switch (val)
		{
			case DTK_MICROSEC:
#ifdef HAVE_INT64_TIMESTAMP
				result = tm->tm_sec * USECS_PER_SEC + fsec;
#else
				result = (tm->tm_sec + fsec) * 1000000;
#endif
				break;

			case DTK_MILLISEC:
#ifdef HAVE_INT64_TIMESTAMP
				result = tm->tm_sec * INT64CONST(1000) + fsec / INT64CONST(1000);
#else
				result = (tm->tm_sec + fsec) * 1000;
#endif
				break;

			case DTK_SECOND:
#ifdef HAVE_INT64_TIMESTAMP
				result = tm->tm_sec + fsec / USECS_PER_SEC;
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

			case DTK_TZ:
			case DTK_TZ_MINUTE:
			case DTK_TZ_HOUR:
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
						 errmsg("\"time\" units \"%s\" not recognized",
								DatumGetCString(DirectFunctionCall1(textout,
												 PointerGetDatum(units))))));

				result = 0;
		}
	}
	else if (type == RESERV && val == DTK_EPOCH)
	{
#ifdef HAVE_INT64_TIMESTAMP
		result = time / 1000000.0;
#else
		result = time;
#endif
	}
	else
	{
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("\"time\" units \"%s\" not recognized",
						DatumGetCString(DirectFunctionCall1(textout,
												 PointerGetDatum(units))))));
		result = 0;
	}

	PG_RETURN_FLOAT8(result);
}
