on_sdb_query_dbe_connected (SymbolDBEngine *dbe, SymbolDBQuery *query)
{
	g_return_if_fail (SYMBOL_DB_IS_QUERY (query));

	if (!query->priv->stmt && query->priv->sql_stmt)
	{
		query->priv->stmt =
			symbol_db_engine_get_statement (query->priv->dbe_selected,
			                                query->priv->sql_stmt);
	}
}
