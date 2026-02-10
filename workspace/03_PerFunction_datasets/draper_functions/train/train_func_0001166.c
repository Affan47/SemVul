e_cal_backend_http_open (ECalBackendSync *backend,
                         EDataCal *cal,
                         GCancellable *cancellable,
                         gboolean only_if_exists,
                         GError **perror)
{
	ECalBackendHttp *cbhttp;
	ECalBackendHttpPrivate *priv;
	ESource *source;
	ESourceRegistry *registry;
	ESourceWebdav *webdav_extension;
	const gchar *extension_name;
	const gchar *cache_dir;
	gboolean opened = TRUE;
	gchar *tmp;
	GError *local_error = NULL;

	cbhttp = E_CAL_BACKEND_HTTP (backend);
	priv = cbhttp->priv;


	if (priv->opened)
		return;

	source = e_backend_get_source (E_BACKEND (backend));
	cache_dir = e_cal_backend_get_cache_dir (E_CAL_BACKEND (backend));

	registry = e_cal_backend_get_registry (E_CAL_BACKEND (backend));

	extension_name = E_SOURCE_EXTENSION_WEBDAV_BACKEND;
	webdav_extension = e_source_get_extension (source, extension_name);

	g_object_set (cbhttp->priv->soup_session, SOUP_SESSION_SSL_STRICT, TRUE, NULL);
	e_source_webdav_unset_temporary_ssl_trust (webdav_extension);

	if (priv->source_changed_id == 0) {
		priv->source_changed_id = g_signal_connect (
			source, "changed",
			G_CALLBACK (source_changed_cb), cbhttp);
	}


	tmp = priv->uri;
	priv->uri = NULL;
	g_free (tmp);

	if (priv->store == NULL) {

		e_cal_backend_cache_remove (cache_dir, "cache.xml");
		priv->store = e_cal_backend_store_new (
			cache_dir, E_TIMEZONE_CACHE (backend));
		e_cal_backend_store_load (priv->store);

		if (!priv->store) {
			g_propagate_error (
				perror, EDC_ERROR_EX (OtherError,
				_("Could not create cache file")));
			return;
		}
	}

	e_cal_backend_set_writable (E_CAL_BACKEND (backend), FALSE);

	if (e_backend_get_online (E_BACKEND (backend))) {
		const gchar *uri;

		uri = cal_backend_http_ensure_uri (cbhttp);

		opened = cal_backend_http_load (
			cbhttp, cancellable,
			uri, &local_error);

		if (g_error_matches (local_error, SOUP_HTTP_ERROR, SOUP_STATUS_UNAUTHORIZED)) {
			g_clear_error (&local_error);
			opened = e_source_registry_authenticate_sync (
				registry, source,
				E_SOURCE_AUTHENTICATOR (backend),
				cancellable, &local_error);
		}

		if (local_error != NULL)
			g_propagate_error (perror, g_error_copy (local_error));
	}

	if (opened) {
		if (!priv->reload_timeout_id)
			priv->reload_timeout_id = e_source_refresh_add_timeout (source, NULL, http_cal_reload_cb, backend, NULL);
	}
}
