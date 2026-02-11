cache_refresh_if_needed (EBookBackend *backend)
{
	EBookBackendGooglePrivate *priv;
	gboolean is_online;

	priv = E_BOOK_BACKEND_GOOGLE_GET_PRIVATE (backend);

	g_debug (G_STRFUNC);

	is_online = e_backend_get_online (E_BACKEND (backend));

	if (!is_online || !backend_is_authorized (backend)) {
		g_debug ("We are not connected to Google%s.", (!is_online) ? " (offline mode)" : "");
		return;
	}

	if (!priv->refresh_id) {

		refresh_local_cache_cb (NULL, backend);

		priv->refresh_id = e_source_refresh_add_timeout (
			e_backend_get_source (E_BACKEND (backend)),
			NULL,
			refresh_local_cache_cb,
			backend,
			NULL);
	} else if (g_hash_table_size (priv->system_groups_by_id) == 0) {
		get_groups (backend);
	}

	return;
}
