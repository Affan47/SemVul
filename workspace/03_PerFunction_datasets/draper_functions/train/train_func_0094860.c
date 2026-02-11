sdb_query_execute_real (SymbolDBQuery *query)
{
	GdaDataModel *data_model;
	SymbolDBQueryPriv *priv = query->priv;

	if (!symbol_db_engine_is_connected (priv->dbe_selected))
	{
		g_warning ("Attempt to make a query when database is not connected");
		return GINT_TO_POINTER (-1);
	}
	if (symbol_db_engine_is_scanning (priv->dbe_selected))
		return GINT_TO_POINTER (-1);

	if (!priv->sql_stmt)
		sdb_query_update (query);
	else if (!priv->stmt)
		priv->stmt = symbol_db_engine_get_statement (priv->dbe_selected,
		                                             priv->sql_stmt);
	data_model = symbol_db_engine_execute_select (priv->dbe_selected,
	                                              priv->stmt,
	                                              priv->params);

	if (!data_model) return GINT_TO_POINTER (-1);
	return symbol_db_query_result_new (data_model,
	                                   priv->fields,
	                                   symbol_db_engine_get_type_conversion_hash (priv->dbe_selected),
	                                   symbol_db_engine_get_project_directory (priv->dbe_selected));
}
