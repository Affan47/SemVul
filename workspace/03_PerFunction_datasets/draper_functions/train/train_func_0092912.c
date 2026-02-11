book_backend_sql_exec (sqlite3 *db,
                       const gchar *stmt,
                       gint (*callback)(gpointer ,gint,gchar **,gchar **),
                       gpointer data,
                       GError **error)
{
	if (booksql_debug ())
		book_backend_sql_debug (db, stmt, callback, data, error);

	return book_backend_sql_exec_real (db, stmt, callback, data, error);
}
