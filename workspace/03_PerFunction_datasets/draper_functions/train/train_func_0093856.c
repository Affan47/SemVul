midgard_core_query_execute (MidgardConnection *mgd, const gchar *query, gboolean ignore_error)
{
	g_assert(mgd);
	g_assert(query != NULL);

	GdaStatement *stmt;
	GError *lerror = NULL;
	gint number = 0;


	if (!mgd->priv->parser) {
		mgd->priv->parser = gda_connection_create_parser (mgd->priv->connection);
		if (!mgd->priv->parser)
			mgd->priv->parser = gda_sql_parser_new ();
	}

	if (MGD_CNC_DEBUG (mgd))
		g_debug("query = %s", query);


	stmt = gda_sql_parser_parse_string (mgd->priv->parser, query, NULL, &lerror);
	if (stmt) {
		number = gda_connection_statement_execute_non_select (mgd->priv->connection, stmt,
								      NULL, NULL, &lerror);
		g_object_unref (stmt);
	}

	if(!ignore_error){


		if (!stmt || (number == -1)) {


			g_warning ("Error executing '%s': %s\n", query,
				   lerror && lerror->message ? lerror->message : "No detail");
		}
	}

	if (lerror)
		g_error_free (lerror);

	return (number);
}
