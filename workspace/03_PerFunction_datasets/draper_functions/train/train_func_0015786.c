sdb_engine_free_cached_queries (SymbolDBEngine *dbe)
{
	SymbolDBEnginePriv *priv;
	gint i;
	static_query_node *node;

	priv = dbe->priv;

	for (i = 0; i < PREP_QUERY_COUNT; i++)
	{
		node = priv->static_query_list[i];

		if (node != NULL && node->stmt != NULL)
		{

			g_object_unref (node->stmt);
			node->stmt = NULL;
		}

		if (node != NULL && node->plist != NULL)
		{

			g_object_unref (node->plist);
			node->plist = NULL;
		}


		g_free (node);
		priv->static_query_list[i] = NULL;
	}
}
