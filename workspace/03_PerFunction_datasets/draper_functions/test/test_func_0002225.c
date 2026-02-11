gda_sql_statement_delete_serialize (gpointer stmt)
{
	GString *string;
	gchar *str;
	GdaSqlStatementDelete *delete = (GdaSqlStatementDelete *) stmt;

	g_return_val_if_fail (stmt, NULL);

	string = g_string_new ("\"contents\":{");


	g_string_append (string, "\"table\":");
	str = gda_sql_table_serialize (delete->table);
	g_string_append (string, str);
	g_free (str);


	if (delete->cond) {
		g_string_append (string, ",\"condition\":");
		str = gda_sql_expr_serialize (delete->cond);
		g_string_append (string, str);
		g_free (str);
	}
	g_string_append_c (string, '}');
	str = string->str;
	g_string_free (string, FALSE);
	return str;
}
