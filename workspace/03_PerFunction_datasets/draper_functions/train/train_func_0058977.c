odbc_get_concise_sql_type(SQLSMALLINT type, SQLSMALLINT interval)
{
#define TYPE_NORMAL(t) case t: return type;
#define TYPE_VERBOSE_START(t) \
	case t: switch (interval) {
#define TYPE_VERBOSE_DATE(t, interval, concise, old) \
	case interval: return concise;
#define TYPE_VERBOSE_END(t) \
	}

	switch (type) {
		SQL_TYPES;
	}
	return 0;
#undef TYPE_NORMAL
#undef TYPE_VERBOSE_START
#undef TYPE_VERBOSE_DATE
#undef TYPE_VERBOSE_END
}
