sdb_query_execute (SymbolDBQuery *query)
{
	SymbolDBQueryResult *result;
	switch (query->priv->mode)
	{
		case IANJUTA_SYMBOL_QUERY_MODE_SYNC:
			result = sdb_query_execute_real (query);

			if (GPOINTER_TO_INT (result) == -1)
				return NULL;


			if (result == NULL || symbol_db_query_result_is_empty (result))
			{
				if (result != NULL)
					g_object_unref (result);
				return NULL;
			}
			return IANJUTA_ITERABLE (result);
		case IANJUTA_SYMBOL_QUERY_MODE_ASYNC:
			query->priv->async_run_count++;
			if (query->priv->async_poll_id == 0)
			{
				query->priv->async_poll_id =
					g_idle_add (on_sdb_query_async_poll, query);
			}
			g_thread_new ("SymbolDBQuery Thread", sdb_query_async_run,
			              g_object_ref (query));
			return NULL;
		case IANJUTA_SYMBOL_QUERY_MODE_QUEUED:
			query->priv->query_queued = TRUE;


			on_sdb_query_dbe_scan_end (NULL, 0, query);
			break;
		default:
			g_warn_if_reached ();
	}
	return NULL;
}
