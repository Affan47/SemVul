e_ews_backend_ref_connection_sync (EEwsBackend *backend,
                                   GCancellable *cancellable,
                                   GError **error)
{
	EEwsConnection *connection = NULL;
	CamelEwsSettings *settings;
	gchar *hosturl;
	gboolean success;

	g_return_val_if_fail (E_IS_EWS_BACKEND (backend), NULL);

	g_mutex_lock (&backend->priv->connection_lock);
	if (backend->priv->connection != NULL)
		connection = g_object_ref (backend->priv->connection);
	g_mutex_unlock (&backend->priv->connection_lock);


	if (connection != NULL)
		return connection;

	settings = ews_backend_get_settings (backend);
	hosturl = camel_ews_settings_dup_hosturl (settings);
	connection = e_ews_connection_new (hosturl, settings);
	g_free (hosturl);

	success = e_backend_authenticate_sync (
		E_BACKEND (backend),
		E_SOURCE_AUTHENTICATOR (connection),
		cancellable, error);

	if (success) {
		g_mutex_lock (&backend->priv->connection_lock);
		if (backend->priv->connection != NULL)
			g_object_unref (backend->priv->connection);
		backend->priv->connection = g_object_ref (connection);
		g_mutex_unlock (&backend->priv->connection_lock);
	} else {
		g_object_unref (connection);
		connection = NULL;
	}

	return connection;
}
