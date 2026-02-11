sdb_query_handle_result (SymbolDBQuery *query, SymbolDBQueryResult *result)
{
	if (GPOINTER_TO_INT (result) == -1)
	{
		g_warning ("Error in executing query");
		g_signal_emit_by_name (query, "async-result", NULL);
	}
	else
	{
		if (symbol_db_query_result_is_empty (result))
		{
			g_signal_emit_by_name (query, "async-result", NULL);
		}
		else
		{
			g_signal_emit_by_name (query, "async-result", result);
		}
		if (result)
			g_object_unref (result);
	}
}
