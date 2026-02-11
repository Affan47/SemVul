db_open(struct realtime_sqlite3_db *db)
{
	ao2_lock(db);
	if (sqlite3_open(db->filename, &db->handle) != SQLITE_OK) {
		ast_log(LOG_WARNING, "Could not open %s: %s\n", db->filename, sqlite3_errmsg(db->handle));
		ao2_unlock(db);
		return -1;
	}

	if (db->debug) {
		sqlite3_trace(db->handle, trace_cb, db);
	} else {
		sqlite3_trace(db->handle, NULL, NULL);
	}

	ao2_unlock(db);

	return 0;
}
