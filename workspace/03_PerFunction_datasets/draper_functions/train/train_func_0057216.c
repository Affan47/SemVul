ast_db_put(const char *family, const char *key, const char *value)
{
	char fullkey[MAX_DB_FIELD];
	size_t fullkey_len;
	int res = 0;

	if (strlen(family) + strlen(key) + 2 > sizeof(fullkey) - 1) {
		ast_log(LOG_WARNING, "Family and key length must be less than %zu bytes\n", sizeof(fullkey) - 3);
		return -1;
	}

	fullkey_len = snprintf(fullkey, sizeof(fullkey), "/%s/%s", family, key);

	ast_mutex_lock(&dblock);
	if (sqlite3_bind_text(put_stmt, 1, fullkey, fullkey_len, SQLITE_STATIC) != SQLITE_OK) {
		ast_log(LOG_WARNING, "Couldn't bind key to stmt: %s\n", sqlite3_errmsg(astdb));
		res = -1;
	} else if (sqlite3_bind_text(put_stmt, 2, value, -1, SQLITE_STATIC) != SQLITE_OK) {
		ast_log(LOG_WARNING, "Couldn't bind value to stmt: %s\n", sqlite3_errmsg(astdb));
		res = -1;
	} else if (sqlite3_step(put_stmt) != SQLITE_DONE) {
		ast_log(LOG_WARNING, "Couldn't execute statment: %s\n", sqlite3_errmsg(astdb));
		res = -1;
	}

	sqlite3_reset(put_stmt);
	db_sync();
	ast_mutex_unlock(&dblock);

	return res;
}
