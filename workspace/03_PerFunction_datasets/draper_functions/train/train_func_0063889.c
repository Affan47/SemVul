sdb_model_project_update_sql_stmt (SymbolDBModel *model)
{
	SymbolDBModelProjectPriv *priv;

	g_return_if_fail (SYMBOL_DB_IS_MODEL_PROJECT (model));
	priv = SYMBOL_DB_MODEL_PROJECT (model)->priv;

	priv->stmt = symbol_db_engine_get_statement (priv->dbe, SDB_MODEL_PROJECT_SQL);
	gda_statement_get_parameters (priv->stmt, &priv->params, NULL);
	priv->param_parent_id = gda_set_get_holder (priv->params, "parent");
	priv->param_limit = gda_set_get_holder (priv->params, "limit");
	priv->param_offset = gda_set_get_holder (priv->params, "offset");
}
