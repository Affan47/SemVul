sdb_engine_get_tuple_id_by_unique_name5 (SymbolDBEngine * dbe,
										 static_query_type qtype,
										 gchar * param_key1,
										 GValue * value1,
										 gchar * param_key2,
										 GValue * value2,
										 gchar * param_key3,
										 GValue * value3,
										 gchar * param_key4,
										 GValue * value4,
										 gchar * param_key5,
										 GValue * value5)
{
	const GdaSet *plist;
	const GdaStatement *stmt;
	GdaHolder *param;
	GdaDataModel *data_model;
	const GValue *num;
	gint table_id;
	SymbolDBEnginePriv *priv;

	priv = dbe->priv;


	if ((stmt = sdb_engine_get_statement_by_query_id (dbe, qtype)) == NULL)
	{
		g_warning ("Query is null");
		return -1;
	}

	plist = sdb_engine_get_query_parameters_list (dbe, qtype);

	if ((param = gda_set_get_holder ((GdaSet*)plist, param_key1)) == NULL)
	{
		g_warning ("sdb_engine_get_tuple_id_by_unique_name5: param is NULL "
				   "from pquery!\n");
		return -1;
	}

	gda_holder_set_value (param, value1, NULL);


	if ((param = gda_set_get_holder ((GdaSet*)plist, param_key2)) == NULL)
	{
		g_warning ("sdb_engine_get_tuple_id_by_unique_name5: "
				   "param is NULL from pquery!");
		return -1;
	}

	gda_holder_set_value (param, value2, NULL);


	if ((param = gda_set_get_holder ((GdaSet*)plist, param_key3)) == NULL)
	{
		g_warning ("sdb_engine_get_tuple_id_by_unique_name5: "
				   "param is NULL from pquery!");
		return -1;
	}

	gda_holder_set_value (param, value3, NULL);


	if ((param = gda_set_get_holder ((GdaSet*)plist, param_key4)) == NULL)
	{
		g_warning ("sdb_engine_get_tuple_id_by_unique_name5: "
				   "param is NULL from pquery!");
		return -1;
	}

	gda_holder_set_value (param, value4, NULL);


	if ((param = gda_set_get_holder ((GdaSet*)plist, param_key5)) == NULL)
	{
		g_warning ("sdb_engine_get_tuple_id_by_unique_name5: "
		           "param is NULL from pquery!");
		return -1;
	}

	gda_holder_set_value (param, value5, NULL);


	data_model = gda_connection_statement_execute_select (priv->db_connection,
														  (GdaStatement*)stmt,
														  (GdaSet*)plist, NULL);

	if (!GDA_IS_DATA_MODEL (data_model) ||
		gda_data_model_get_n_rows (GDA_DATA_MODEL (data_model)) <= 0)
	{
		if (data_model != NULL)
			g_object_unref (data_model);

		return -1;
	}


	num = gda_data_model_get_value_at (GDA_DATA_MODEL (data_model), 0, 0, NULL);

	table_id = g_value_get_int (num);
	g_object_unref (data_model);
	return table_id;
}
