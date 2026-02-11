odbc_set_concise_sql_type(SQLSMALLINT concise_type, struct _drecord * drec, int check_only)
{
	SQLSMALLINT type = concise_type, interval_code = 0;

#define TYPE_NORMAL(t) case t: break;
#define TYPE_VERBOSE_START(t)
#define TYPE_VERBOSE_DATE(t, interval, concise, old) \
	case old: concise_type = concise; \
	case concise: type = t; interval_code = interval; break;
#define TYPE_VERBOSE_END(t)

	switch (type) {
		SQL_TYPES;
	default:
		return SQL_ERROR;
	}
	if (!check_only) {
		drec->sql_desc_concise_type = concise_type;
		drec->sql_desc_type = type;
		drec->sql_desc_datetime_interval_code = interval_code;

		switch (drec->sql_desc_type) {
		case SQL_NUMERIC:
		case SQL_DECIMAL:
			drec->sql_desc_precision = 38;
			drec->sql_desc_scale = 0;
			break;

		}
	}
	return SQL_SUCCESS;
#undef TYPE_NORMAL
#undef TYPE_VERBOSE_START
#undef TYPE_VERBOSE_DATE
#undef TYPE_VERBOSE_END
}
