new_connection_cb (DBusGProxy *proxy, const char *path, gpointer user_data)
{
	NMRemoteSettings *self = NM_REMOTE_SETTINGS (user_data);
	NMRemoteSettingsPrivate *priv = NM_REMOTE_SETTINGS_GET_PRIVATE (self);
	NMRemoteConnection *connection = NULL;


	connection = g_hash_table_lookup (priv->pending, path);
	if (connection)
		return connection;
	connection = g_hash_table_lookup (priv->connections, path);
	if (connection)
		return connection;


	connection = nm_remote_connection_new (priv->bus, path);
	if (connection) {
		g_async_initable_init_async (G_ASYNC_INITABLE (connection),
		                             G_PRIORITY_DEFAULT, NULL,
		                             connection_inited, self);


		move_connection (self, connection, NULL, priv->pending);
		g_object_unref (connection);
	}
	return connection;
}
