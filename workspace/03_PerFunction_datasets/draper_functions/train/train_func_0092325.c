gda_sql_parser_parse_string_as_batch (GdaSqlParser *parser, const gchar *sql, const gchar **remain,
				      GError **error)
{
	GdaBatch *batch;
	GdaStatement *stmt;
	const gchar *int_sql;
	gboolean allok = TRUE;
	gint n_stmt = 0;
	gint n_empty = 0;

	g_return_val_if_fail (GDA_IS_SQL_PARSER (parser), NULL);
	g_return_val_if_fail (parser->priv, NULL);

	if (remain)
		*remain = NULL;

	batch = gda_batch_new ();
	if (!sql)
		return batch;

	gda_mutex_lock (parser->priv->mutex);

	int_sql = sql;
	while (int_sql && allok) {
		GError *lerror = NULL;
		const gchar *int_remain = NULL;

		stmt = gda_sql_parser_parse_string (parser, int_sql, &int_remain, &lerror);
		if (stmt) {
			if (gda_statement_is_useless (stmt))
				n_empty++;
			else {
				gda_batch_add_statement (batch, stmt);
				n_stmt++;
			}
			g_object_unref (stmt);
		}
		else if (lerror && (lerror->domain == GDA_SQL_PARSER_ERROR) &&
			 (lerror->code == GDA_SQL_PARSER_EMPTY_SQL_ERROR))
			n_empty++;
		else {
			if (int_remain)
				allok = FALSE;
			if (lerror) {
				g_propagate_error (error, lerror);
				lerror = NULL;
			}
		}
		if (lerror)
			g_error_free (lerror);
		int_sql = int_remain;
	}

	if ((n_stmt == 0) && (n_empty != 0))
		g_set_error (error, GDA_SQL_PARSER_ERROR, GDA_SQL_PARSER_EMPTY_SQL_ERROR,
			      "%s", _("SQL code does not contain any statement"));

	if (!allok || (n_stmt == 0)) {
		if (remain)
			*remain = int_sql;
		g_object_unref (batch);
		batch = NULL;
	}

	gda_mutex_unlock (parser->priv->mutex);

	return batch;
}
