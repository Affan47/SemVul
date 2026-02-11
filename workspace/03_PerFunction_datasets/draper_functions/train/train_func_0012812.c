cache_set_last_update (EBookBackend *backend,
                       GTimeVal *tv)
{
	EBookBackendGooglePrivate *priv;
	gchar *_time;

	priv = E_BOOK_BACKEND_GOOGLE_GET_PRIVATE (backend);

	if (tv)
		_time = g_time_val_to_iso8601 (tv);
	else
		_time = NULL;

	g_mutex_lock (&priv->cache_lock);
	if (tv)
		e_book_backend_cache_set_time (priv->cache, _time);
	else
		e_file_cache_remove_object (E_FILE_CACHE (priv->cache), "last_update_time");
	g_mutex_unlock (&priv->cache_lock);
	g_free (_time);
}
