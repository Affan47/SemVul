sdb_query_result_init (SymbolDBQueryResult *result)
{
	gint i;

	result->priv = SYMBOL_DB_QUERY_RESULT_GET_PRIVATE (result);
	result->priv->col_map = g_new (gint, IANJUTA_SYMBOL_FIELD_END);
	for (i = 0; i < IANJUTA_SYMBOL_FIELD_END; i++)
		result->priv->col_map[i] = -1;
	result->priv->result_is_empty = TRUE;
}
