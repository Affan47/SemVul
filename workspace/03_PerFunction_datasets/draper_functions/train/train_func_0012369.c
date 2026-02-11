gda_postgres_recordset_new_cursor (GdaConnection *cnc, GdaPostgresPStmt *ps, GdaSet *exec_params,
				   gchar *cursor_name, GType *col_types)
{
	GdaPostgresRecordset *model;
        PostgresConnectionData *cdata;

        g_return_val_if_fail (GDA_IS_CONNECTION (cnc), NULL);
        g_return_val_if_fail (ps, NULL);

	cdata = (PostgresConnectionData*) gda_connection_internal_get_provider_data (cnc);
	if (!cdata)
		return NULL;


	gchar *str;
	int status;
	PGresult *pg_res;

	str = g_strdup_printf ("FETCH FORWARD 1 FROM %s;", cursor_name);
	pg_res = PQexec (cdata->pconn, str);
	g_free (str);
	status = PQresultStatus (pg_res);
	if (!pg_res || (status != PGRES_TUPLES_OK)) {
		_gda_postgres_make_error (cdata->cnc, cdata->pconn, pg_res, NULL);
		if (pg_res) {
			PQclear (pg_res);
			pg_res = NULL;
		}
	}
	else {
		PGresult *tmp_res;
		str = g_strdup_printf ("MOVE BACKWARD 1 FROM %s;", cursor_name);
		tmp_res = PQexec (cdata->pconn, str);
		g_free (str);
		if (tmp_res)
			PQclear (tmp_res);
	}


	finish_prep_stmt_init (cdata, ps, pg_res, col_types);
	if (pg_res)
		PQclear (pg_res);


	model = g_object_new (GDA_TYPE_POSTGRES_RECORDSET, "connection", cnc,
			      "prepared-stmt", ps, "model-usage",
			      GDA_DATA_MODEL_ACCESS_CURSOR_FORWARD | GDA_DATA_MODEL_ACCESS_CURSOR_BACKWARD,
			      "exec-params", exec_params, NULL);
	model->priv->pconn = cdata->pconn;
	model->priv->cursor_name = cursor_name;
	gboolean fetch_error;
	fetch_next_chunk (model, &fetch_error, NULL);

	return GDA_DATA_MODEL (model);
}
