parse_field_spec (GdaDataPivot *pivot, const gchar *field, const gchar *alias, GError **error)
{
	GdaSqlParser *parser;
	gchar *sql;
	GdaStatement *stmt;
	const gchar *remain;
	GError *lerror = NULL;

	g_return_val_if_fail (field, FALSE);

	if (! bind_source_model (pivot, error))
		return NULL;

	parser = gda_connection_create_parser (pivot->priv->vcnc);
	g_assert (parser);
	if (alias && *alias) {
		gchar *tmp, *ptr;
		tmp = g_strdup (alias);
		for (ptr = tmp; *ptr; ptr++) {
			if (g_ascii_isdigit (*ptr)) {
				if (ptr == tmp)
					*ptr = '_';
			}
			else if (! g_ascii_isalpha (*ptr))
				*ptr = '_';
		}
		sql = g_strdup_printf ("SELECT %s AS %s FROM " TABLE_NAME, field, tmp);
		g_free (tmp);
	}
	else
		sql = g_strdup_printf ("SELECT %s FROM " TABLE_NAME, field);
	stmt = gda_sql_parser_parse_string (parser, sql, &remain, &lerror);
	g_free (sql);
	g_object_unref (parser);
	if (!stmt || remain) {
		g_set_error (error, GDA_DATA_PIVOT_ERROR, GDA_DATA_PIVOT_FIELD_FORMAT_ERROR,
			     _("Wrong field format error: %s"),
			     lerror && lerror->message ? lerror->message : _("No detail"));
		g_clear_error (&lerror);
		return NULL;
	}


	GdaSqlStatement *sqlst = NULL;
	g_object_get ((GObject*) stmt, "structure", &sqlst, NULL);

	if (sqlst->stmt_type != GDA_SQL_STATEMENT_SELECT) {
		g_object_unref (stmt);
		gda_sql_statement_free (sqlst);
		g_set_error (error, GDA_DATA_PIVOT_ERROR, GDA_DATA_PIVOT_FIELD_FORMAT_ERROR,
			     "%s", _("Wrong field format"));
		return NULL;
	}


	GdaDataModel *model;
	model = gda_connection_statement_execute_select (pivot->priv->vcnc, stmt, NULL, &lerror);
	g_object_unref (stmt);
	if (!model) {
		g_set_error (error, GDA_DATA_PIVOT_ERROR, GDA_DATA_PIVOT_FIELD_FORMAT_ERROR,
			     _("Wrong field format error: %s"),
			     lerror && lerror->message ? lerror->message : _("No detail"));
		g_clear_error (&lerror);
		return NULL;
	}


	g_object_unref (model);
	return sqlst;
}
