get_select_statement_by_query_id (GdaConnection * cnc, GdaSet **plist)
{
	GdaStatement *stmt;
	gchar *sql = "SELECT count(*) FROM SYM_TYPE";

	GdaSqlParser *parser = gda_connection_create_parser (cnc);


	stmt = gda_sql_parser_parse_string (parser, sql, NULL,
										 NULL);

	if (gda_statement_get_parameters ((GdaStatement*)stmt,
									  plist, NULL) == FALSE)
	{
		g_warning ("Error on getting parameters");
	}

	return stmt;
}
