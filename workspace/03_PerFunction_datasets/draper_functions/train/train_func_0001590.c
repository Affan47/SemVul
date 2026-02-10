handle_missing_table(struct realtime_sqlite3_db *db, const char *table, va_list ap)
{
	const char *column;
	int type, first = 1, res;
	size_t sz;
	struct ast_str *sql;

	if (!(sql = ast_str_create(128))) {
		return -1;
	}

	while ((column = va_arg(ap, typeof(column))) && (type = va_arg(ap, typeof(type))) && (sz = va_arg(ap, typeof(sz)))) {
		if (first) {
			ast_str_set(&sql, 0, "CREATE TABLE IF NOT EXISTS %s (%s %s", sqlite3_escape_table(table),
					sqlite3_escape_column(column), get_sqlite_column_type(type));
			first = 0;
		} else {
			ast_str_append(&sql, 0, ", %s %s", sqlite3_escape_column(column), get_sqlite_column_type(type));
		}
	}

	ast_str_append(&sql, 0, ")");

	res = realtime_sqlite3_execute_handle(db, ast_str_buffer(sql), NULL, NULL, 1) < 0 ? -1 : 0;
	ast_free(sql);

	return res;
}
