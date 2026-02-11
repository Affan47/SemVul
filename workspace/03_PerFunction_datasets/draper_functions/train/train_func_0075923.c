geocode_reverse_resolve_async (GeocodeReverse     *object,
			       GCancellable       *cancellable,
			       GAsyncReadyCallback callback,
			       gpointer            user_data)
{
	GSimpleAsyncResult *simple;
	SoupMessage *query;
	char *cache_path;

	g_return_if_fail (GEOCODE_IS_REVERSE (object));

	simple = g_simple_async_result_new (G_OBJECT (object),
					    callback,
					    user_data,
					    geocode_reverse_resolve_async);

	query = get_resolve_query_for_params (object->priv->ht);

	cache_path = _geocode_glib_cache_path_for_query (query);
	if (cache_path == NULL) {
		soup_session_queue_message (object->priv->soup_session,
                                            query,
					    on_query_data_loaded,
					    simple);
	} else {
		GFile *cache;

		cache = g_file_new_for_path (cache_path);
		g_object_set_data_full (G_OBJECT (cache), "query", query, (GDestroyNotify) g_object_unref);
		g_file_load_contents_async (cache,
					    cancellable,
					    on_cache_data_loaded,
					    simple);
		g_object_unref (cache);
	}
}
