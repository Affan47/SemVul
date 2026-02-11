symbol_db_engine_project_exists (SymbolDBEngine * dbe,
							   	const gchar * project_name,
    							const gchar * project_version)
{
	SymbolDBEnginePriv *priv;
	GValue v = {0};
	const GdaSet *plist;
	const GdaStatement *stmt;
	GdaHolder *param;
	GdaDataModel *data_model;

	priv = dbe->priv;

	SDB_LOCK(priv);

	g_return_val_if_fail (priv->db_connection != NULL, FALSE);


	if ((stmt = sdb_engine_get_statement_by_query_id (dbe,
	    PREP_QUERY_GET_PROJECT_ID_BY_UNIQUE_NAME)) == NULL)
	{
		g_warning ("Query is null");
		SDB_UNLOCK(priv);
		return FALSE;
	}

	plist = sdb_engine_get_query_parameters_list (dbe,
	    PREP_QUERY_GET_PROJECT_ID_BY_UNIQUE_NAME);

	if ((param = gda_set_get_holder ((GdaSet*)plist, "prjname")) == NULL)
	{
		g_warning ("sdb_engine_get_tuple_id_by_unique_name: param is NULL "
				   "from pquery!\n");
		SDB_UNLOCK(priv);
		return FALSE;
	}

	SDB_PARAM_SET_STRING (param, project_name);

	if ((param = gda_set_get_holder ((GdaSet*)plist, "prjversion")) == NULL)
	{
		g_warning ("sdb_engine_get_tuple_id_by_unique_name: param is NULL "
				   "from pquery!\n");
		SDB_UNLOCK(priv);
		return FALSE;
	}

	SDB_PARAM_SET_STRING (param, project_version);


	data_model = gda_connection_statement_execute_select (priv->db_connection,
														  (GdaStatement*)stmt,
														  (GdaSet*)plist, NULL);

	if (!GDA_IS_DATA_MODEL (data_model) ||
		gda_data_model_get_n_rows (GDA_DATA_MODEL (data_model)) <= 0)
	{
		if (data_model != NULL)
			g_object_unref (data_model);
		SDB_UNLOCK(priv);
		return FALSE;
	}


	g_object_unref (data_model);

	SDB_UNLOCK(priv);

	return TRUE;
}
