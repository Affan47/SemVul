bxgrid_db_query( MYSQL *mysql_cxn, const char *queryfmt, ... )
{
	va_list args;
	va_start(args, queryfmt);
	char query[PFS_LINE_MAX];

	vsprintf(query, queryfmt, args);

	debug(D_BXGRID, "db_query: %s", query);
	if (mysql_query(mysql_cxn, query) < 0) {
		debug(D_BXGRID, "couldn't execute query '%s': %s", query, mysql_error(mysql_cxn));
	}

	va_end(args);
	return mysql_store_result(mysql_cxn);
}
