sqlite_set_value(MetaDataType type,const char *key_a,const char *key_b, MetaDataContentType content_type, const char *content)
{
	sqlite3_stmt *const stmt = meta_data_sqlite_stmt[META_DATA_SQL_SET];
	int ret;
	sqlite3_reset(stmt);

	ret = sqlite3_bind_int(stmt, 1, content_type);
	if (ret != SQLITE_OK) {
		g_log(MDC_LOG_DOMAIN, G_LOG_LEVEL_WARNING,"sqlite3_bind_int() failed: %s",
				sqlite3_errmsg(meta_data_sqlite_db));
		return FALSE;
	}
	ret = sqlite3_bind_text(stmt, 2, content,-1, NULL);
	if (ret != SQLITE_OK) {
		g_log(MDC_LOG_DOMAIN, G_LOG_LEVEL_WARNING,"sqlite3_bind_text() failed: %s",
				sqlite3_errmsg(meta_data_sqlite_db));
		return FALSE;
	}

	ret = sqlite3_bind_int(stmt, 3, type);
	if (ret != SQLITE_OK) {
		g_log(MDC_LOG_DOMAIN, G_LOG_LEVEL_WARNING,"sqlite3_bind_int() failed: %s",
				sqlite3_errmsg(meta_data_sqlite_db));
		return FALSE;
	}

	ret = sqlite3_bind_text(stmt, 4, key_a,-1, NULL);
	if (ret != SQLITE_OK) {
		g_log(MDC_LOG_DOMAIN, G_LOG_LEVEL_WARNING,"sqlite3_bind_text() failed: %s",
				sqlite3_errmsg(meta_data_sqlite_db));
		return FALSE;
	}

	ret = sqlite3_bind_text(stmt, 5, key_b,-1, NULL);
	if (ret != SQLITE_OK) {
		g_log(MDC_LOG_DOMAIN, G_LOG_LEVEL_WARNING,"sqlite3_bind_text() failed: %s",
				sqlite3_errmsg(meta_data_sqlite_db));
		return FALSE;
	}
	do {
		ret = sqlite3_step(stmt);
	} while (ret == SQLITE_BUSY);

	if (ret != SQLITE_DONE) {
		g_log(MDC_LOG_DOMAIN, G_LOG_LEVEL_WARNING,"%s: sqlite3_step() failed %s::%s content:'%s' : %s",__FUNCTION__, key_a, key_b,content,
				sqlite3_errmsg(meta_data_sqlite_db));
		return FALSE;
	}


	ret = sqlite3_changes(meta_data_sqlite_db);

	sqlite3_reset(stmt);
	sqlite3_clear_bindings(stmt);
	return ret > 0;
}
