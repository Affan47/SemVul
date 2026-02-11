gda_postgres_provider_statement_prepare (GdaServerProvider *provider, GdaConnection *cnc,
					 GdaStatement *stmt, GError **error)
{
	GdaPostgresPStmt *ps;
	PostgresConnectionData *cdata;
	static guint counter = 0;

	g_return_val_if_fail (GDA_IS_CONNECTION (cnc), FALSE);
	g_return_val_if_fail (gda_connection_get_provider (cnc) == provider, FALSE);
	g_return_val_if_fail (GDA_IS_STATEMENT (stmt), FALSE);


	ps = (GdaPostgresPStmt *) gda_connection_get_prepared_statement (cnc, stmt);
	if (ps)
		return TRUE;


	cdata = (PostgresConnectionData*) gda_connection_internal_get_provider_data_error (cnc, error);
	if (!cdata)
		return FALSE;


	GdaSet *params = NULL;
	gchar *sql;
	GSList *used_params = NULL;
	if (! gda_statement_get_parameters (stmt, &params, error))
                return FALSE;
        sql = gda_postgres_provider_statement_to_sql (provider, cnc, stmt, params, GDA_STATEMENT_SQL_PARAMS_AS_DOLLAR,
						      &used_params, error);
        if (!sql)
                goto out_err;


	PGresult *pg_res;
	gchar *prep_stm_name;

	prep_stm_name = g_strdup_printf ("psc%d", counter ++);
	pg_res = PQprepare (cdata->pconn, prep_stm_name, sql, 0, NULL);
	if (!pg_res || (PQresultStatus (pg_res) != PGRES_COMMAND_OK)) {
		_gda_postgres_make_error (cnc, cdata->pconn, pg_res, error);
		g_free (prep_stm_name);
		if (pg_res)
			PQclear (pg_res);
		goto out_err;
	}
	PQclear (pg_res);


        GSList *param_ids = NULL;
        if (used_params) {
                GSList *list;
                for (list = used_params; list; list = list->next) {
                        const gchar *cid;
                        cid = gda_holder_get_id (GDA_HOLDER (list->data));
                        if (cid) {
                                param_ids = g_slist_append (param_ids, g_strdup (cid));

                        }
                        else {
                                g_set_error (error, GDA_SERVER_PROVIDER_ERROR, GDA_SERVER_PROVIDER_PREPARE_STMT_ERROR,
                                             "%s", _("Unnamed parameter is not allowed in prepared statements"));
                                g_slist_foreach (param_ids, (GFunc) g_free, NULL);
                                g_slist_free (param_ids);
				g_free (prep_stm_name);
                                goto out_err;
                        }
                }
        }


        ps = gda_postgres_pstmt_new (cnc, cdata->pconn, prep_stm_name);
	g_free (prep_stm_name);
	gda_pstmt_set_gda_statement (_GDA_PSTMT (ps), stmt);
        _GDA_PSTMT (ps)->param_ids = param_ids;
        _GDA_PSTMT (ps)->sql = sql;
	if (sql_can_cause_date_format_change (sql))
		ps->date_format_change = TRUE;

	gda_connection_add_prepared_statement (cnc, stmt, (GdaPStmt *) ps);
	g_object_unref (ps);

	return TRUE;

 out_err:
	if (used_params)
                g_slist_free (used_params);
        if (params)
                g_object_unref (params);
	g_free (sql);
	return FALSE;
}
