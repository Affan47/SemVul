soup_cache_content_processor_wrap_input (SoupContentProcessor *processor,
					 GInputStream *base_stream,
					 SoupMessage *msg,
					 GError **error)
{
	SoupCache *cache = (SoupCache*) processor;
	SoupCacheEntry *entry;
	SoupCacheability cacheability;
	GInputStream *istream;
	GFile *file;
	StreamHelper *helper;
	time_t request_time, response_time;


	cacheability = soup_cache_get_cacheability (cache, msg);
	entry = soup_cache_entry_lookup (cache, msg);

	if (cacheability & SOUP_CACHE_INVALIDATES) {
		if (entry)
			soup_cache_entry_remove (cache, entry, TRUE);
		return NULL;
	}

	if (cacheability & SOUP_CACHE_VALIDATES) {


		if (entry)
			soup_cache_update_from_conditional_request (cache, msg);
		return NULL;
	}

	if (!(cacheability & SOUP_CACHE_CACHEABLE))
		return NULL;


	if (entry && (entry->dirty || entry->being_validated))
		return NULL;


	if (entry)
		soup_cache_entry_remove (cache, entry, TRUE);

	request_time = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (msg), "request-time"));
	response_time = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (msg), "request-time"));
	entry = soup_cache_entry_new (cache, msg, request_time, response_time);
	entry->hits = 1;
	entry->dirty = TRUE;


	if (!soup_cache_entry_insert (cache, entry, TRUE)) {
		soup_cache_entry_free (entry);
		return NULL;
	}

	entry->cancellable = g_cancellable_new ();
	++cache->priv->n_pending;

	helper = g_slice_new (StreamHelper);
	helper->cache = g_object_ref (cache);
	helper->entry = entry;

	file = get_file_from_entry (cache, entry);
	istream = soup_cache_input_stream_new (base_stream, file);
	g_object_unref (file);

	g_signal_connect (istream, "caching-finished", G_CALLBACK (istream_caching_finished), helper);

	return istream;
}
