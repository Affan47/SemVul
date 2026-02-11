DateTimeParseError(int dterr, const char *str, const char *datatype)
{
	switch (dterr)
	{
		case DTERR_FIELD_OVERFLOW:
			ereport(ERROR,
					(errcode(ERRCODE_DATETIME_FIELD_OVERFLOW),
					 errmsg("date/time field value out of range: \"%s\"",
							str)));
			break;
		case DTERR_MD_FIELD_OVERFLOW:

			ereport(ERROR,
					(errcode(ERRCODE_DATETIME_FIELD_OVERFLOW),
					 errmsg("date/time field value out of range: \"%s\"",
							str),
			errhint("Perhaps you need a different \"datestyle\" setting.")));
			break;
		case DTERR_INTERVAL_OVERFLOW:
			ereport(ERROR,
					(errcode(ERRCODE_INTERVAL_FIELD_OVERFLOW),
					 errmsg("interval field value out of range: \"%s\"",
							str)));
			break;
		case DTERR_TZDISP_OVERFLOW:
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TIME_ZONE_DISPLACEMENT_VALUE),
					 errmsg("time zone displacement out of range: \"%s\"",
							str)));
			break;
		case DTERR_BAD_FORMAT:
		default:
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_DATETIME_FORMAT),
					 errmsg("invalid input syntax for type %s: \"%s\"",
							datatype, str)));
			break;
	}
}
