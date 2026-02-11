delete_file(const char *sdir, int smsg)
{
	SQLHSTMT stmt;
	char sql[PATH_MAX];
	char msgnums[20];
	char *argv[] = { NULL, msgnums };
	struct generic_prepare_struct gps = { .sql = sql, .argc = 2, .argv = argv };
	struct odbc_obj *obj;

	argv[0] = ast_strdupa(sdir);

	obj = ast_odbc_request_obj(odbc_database, 0);
	if (obj) {
		snprintf(msgnums, sizeof(msgnums), "%d", smsg);
		snprintf(sql, sizeof(sql), "DELETE FROM %s WHERE dir=? AND msgnum=?", odbc_table);
		stmt = ast_odbc_prepare_and_execute(obj, generic_prepare, &gps);
		if (!stmt)
			ast_log(AST_LOG_WARNING, "SQL Execute error!\n[%s]\n\n", sql);
		else
			SQLFreeHandle (SQL_HANDLE_STMT, stmt);
		ast_odbc_release_obj(obj);
	} else
		ast_log(AST_LOG_WARNING, "Failed to obtain database object for '%s'!\n", odbc_database);
	return;
}
