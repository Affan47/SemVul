imapx_disconnect_sync (CamelService *service,
                       gboolean clean,
                       GCancellable *cancellable,
                       GError **error)
{
	CamelIMAPXStorePrivate *priv;

	priv = CAMEL_IMAPX_STORE_GET_PRIVATE (service);

	g_mutex_lock (&priv->server_lock);

	g_clear_object (&priv->connected_server);
	g_clear_object (&priv->connecting_server);

	g_mutex_unlock (&priv->server_lock);

	return TRUE;
}
