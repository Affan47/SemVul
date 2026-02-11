list(size_t argc, const char** argv)
{
	char* errMsg;
	int found = 0;
	int rc;

	open_database();

	rc = sqlite3_exec(db, "SELECT * FROM users;", sql_callback_list, &found, &errMsg);
	if (rc != SQLITE_OK) {
#ifdef DEBUG_SQL
		fprintf(stderr, "SQL: ERROR: %s (%d)\n", errMsg, rc);
#endif
		sqlite3_free(errMsg);
		exit(1);
	}

	sqlite3_close(db);
	return 0;
}
