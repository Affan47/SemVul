gda_statement_rewrite_for_default_values (GdaStatement *stmt, GdaSet *params, gboolean remove, GError **error)
{
	GdaSqlStatement *sqlst;
	GdaSqlStatementType type;
	gboolean ok = FALSE;
	g_return_val_if_fail (GDA_IS_STATEMENT (stmt), NULL);
	g_return_val_if_fail (GDA_IS_SET (params), NULL);
	type = gda_statement_get_statement_type (stmt);

	g_object_get (stmt, "structure", &sqlst, NULL);
	if (! gda_sql_statement_check_structure (sqlst, error)) {
		gda_sql_statement_free (sqlst);
		return NULL;
	}

	switch (type) {
	case GDA_SQL_STATEMENT_INSERT:
		if (remove)
			ok = stmt_rewrite_insert_remove ((GdaSqlStatementInsert*) sqlst->contents,
							 params, error);
		else
			ok = stmt_rewrite_insert_default_keyword ((GdaSqlStatementInsert*) sqlst->contents,
								  params, error);
		break;
	case GDA_SQL_STATEMENT_UPDATE:
		if (remove)
			g_set_error (error, GDA_SERVER_PROVIDER_ERROR,
				     GDA_SERVER_PROVIDER_DEFAULT_VALUE_HANDLING_ERROR,
				     "%s", _("Can't rewrite UPDATE statement to handle default values"));
		else
			ok = stmt_rewrite_update_default_keyword ((GdaSqlStatementUpdate*) sqlst->contents,
								  params, error);
		break;
	default:
		g_set_error (error, GDA_SERVER_PROVIDER_ERROR,
			     GDA_SERVER_PROVIDER_DEFAULT_VALUE_HANDLING_ERROR,
			     "%s", _("Can't rewrite statement which is not INSERT or UPDATE"));
		break;
	}

	if (ok)
		return sqlst;
	else {
		gda_sql_statement_free (sqlst);
		return NULL;
	}
}
