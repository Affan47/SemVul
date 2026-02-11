gda_postgres_render_DROP_COLUMN  (GdaServerProvider *provider, GdaConnection *cnc,
				  GdaServerOperation *op, G_GNUC_UNUSED GError **error)
{
	GString *string;
	const GValue *value;
	gchar *sql = NULL;
	gchar *tmp;

	string = g_string_new ("ALTER TABLE ");

	tmp = gda_server_operation_get_sql_identifier_at (op, cnc, provider, "/COLUMN_DESC_P/TABLE_NAME");
	g_string_append (string, tmp);
	g_free (tmp);
	tmp = gda_server_operation_get_sql_identifier_at (op, cnc, provider, "/COLUMN_DESC_P/COLUMN_NAME");
	g_string_append (string, " DROP COLUMN ");
	g_string_append (string, tmp);
	g_free (tmp);

	value = gda_server_operation_get_value_at (op, "/COLUMN_DESC_P/REFERENCED_ACTION");
	if (value && G_VALUE_HOLDS (value, G_TYPE_STRING)) {
		const gchar *str = g_value_get_string (value);
		if (str && *str) {
			g_string_append_c (string, ' ');
			g_string_append (string, str);
		}
	}

	sql = string->str;
	g_string_free (string, FALSE);

	return sql;
}
