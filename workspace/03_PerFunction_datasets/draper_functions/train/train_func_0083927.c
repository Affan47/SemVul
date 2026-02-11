gda_connection_parse_sql_string (GdaConnection *cnc, const gchar *sql, GdaSet **params, GError **error)
{
	GdaStatement *stmt;
	GdaSqlParser *parser = NULL;

	g_return_val_if_fail (!cnc || GDA_IS_CONNECTION (cnc), NULL);
	g_return_val_if_fail (sql, NULL);

	if (params)
		*params = NULL;
	if (cnc)
		parser = gda_connection_create_parser (cnc);
	if (!parser)
		parser = gda_sql_parser_new ();

	stmt = gda_sql_parser_parse_string (parser, sql, NULL, error);
	g_object_unref (parser);
	if (! stmt)
		return NULL;

	if (params && !gda_statement_get_parameters (stmt, params, error)) {
		g_object_unref (stmt);
		return NULL;
	}

	return stmt;
}
