_gda_sqlite_render_DROP_TABLE (GdaServerProvider *provider, GdaConnection *cnc,
			       GdaServerOperation *op, G_GNUC_UNUSED GError **error)
{
	GString *string;
	const GValue *value;
	gchar *sql = NULL;
	gchar *tmp;


	string = g_string_new ("DROP TABLE");

	value = gda_server_operation_get_value_at (op, "/TABLE_DESC_P/TABLE_IFEXISTS");
	if (value && G_VALUE_HOLDS (value, G_TYPE_BOOLEAN) && g_value_get_boolean (value))
		g_string_append (string, " IF EXISTS");

	tmp = gda_server_operation_get_sql_identifier_at (op, cnc, provider, "/TABLE_DESC_P/TABLE_NAME");
	g_string_append_c (string, ' ');
	g_string_append (string, tmp);
	g_free (tmp);

	sql = string->str;
	g_string_free (string, FALSE);

	return sql;
}
