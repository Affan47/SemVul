meta_data_sqlite_prepare(const char *sql)
{
	int ret;
	sqlite3_stmt *stmt;

	ret = sqlite3_prepare_v2(meta_data_sqlite_db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK)
		g_log(MDC_LOG_DOMAIN, G_LOG_LEVEL_ERROR,"sqlite3_prepare_v2() failed: %s",
				sqlite3_errmsg(meta_data_sqlite_db));

	return stmt;
}
