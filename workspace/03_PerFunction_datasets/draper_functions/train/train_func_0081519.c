e_book_client_connect_direct_sync (ESourceRegistry *registry,
                                   ESource *source,
                                   GCancellable *cancellable,
                                   GError **error)
{
	EClient *client;
	EBookClientPrivate *priv;
	EDBusDirectBook *direct_config;
	const gchar *backend_name, *backend_path, *config;
	GError *local_error = NULL;

	client = e_book_client_connect_sync (source, cancellable, error);

	if (!client)
		return NULL;

	priv = E_BOOK_CLIENT_GET_PRIVATE (client);

	direct_config = e_dbus_direct_book_proxy_new_sync (
		g_dbus_proxy_get_connection (G_DBUS_PROXY (priv->dbus_proxy)),
		G_DBUS_PROXY_FLAGS_NONE,
		ADDRESS_BOOK_DBUS_SERVICE_NAME,
		g_dbus_proxy_get_object_path (G_DBUS_PROXY (priv->dbus_proxy)),
		NULL, NULL);

	backend_path = e_dbus_direct_book_get_backend_path (direct_config);
	backend_name = e_dbus_direct_book_get_backend_name (direct_config);
	config = e_dbus_direct_book_get_backend_config (direct_config);

	if (backend_path != NULL && *backend_path != '\0' &&
	    backend_name != NULL && *backend_name != '\0') {
		priv->direct_backend = book_client_load_direct_backend (
			registry, source,
			backend_path,
			backend_name,
			config, &local_error);
		if (local_error != NULL) {
			g_warning (
				"Failed to open addressbook in direct read "
				"access mode, falling back to normal read "
				"access mode. Reason: %s",
				local_error->message);
			g_error_free (local_error);
		}

	} else {
		g_warning (
			"Direct read access mode not supported by the given "
			"backend, falling back to normal read access mode");
	}

	g_object_unref (direct_config);


	if (priv->direct_backend != NULL) {
		gboolean success;


		success = e_book_backend_open_sync (
			priv->direct_backend, cancellable, error);

		if (!success) {
			g_warning (
				"Unable to open direct read access book, "
				"falling back to normal read access mode");
			g_clear_object (&priv->direct_backend);
		}
	}

	return client;

}
