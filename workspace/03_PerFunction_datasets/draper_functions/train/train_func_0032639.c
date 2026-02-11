run_sql_select (GdaConnection *cnc, const gchar *sql)
{
	GdaStatement *stmt;
	GError *error = NULL;
	GdaDataModel *res;
	GdaSqlParser *parser;

	parser = gda_connection_create_parser (cnc);
	stmt = gda_sql_parser_parse_string (parser, sql, NULL, NULL);
	g_object_unref (parser);

        res = gda_connection_statement_execute_select (cnc, stmt, NULL, &error);
        g_object_unref (stmt);
	if (!res)
		g_error ("Could not execute query: %s\n",
			 error && error->message ? error->message : "no detail");
	return res;
}
