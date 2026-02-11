soup_socket_handshake_async (SoupSocket         *sock,
			     GCancellable       *cancellable,
			     SoupSocketCallback  callback,
			     gpointer            user_data)
{
	SoupSocketPrivate *priv = SOUP_SOCKET_GET_PRIVATE (sock);
	SoupSocketAsyncConnectData *data;

	priv->ssl = TRUE;

	data = g_slice_new (SoupSocketAsyncConnectData);
	data->sock = g_object_ref (sock);
	data->callback = callback;
	data->user_data = user_data;

	if (priv->async_context && !priv->use_thread_context)
		g_main_context_push_thread_default (priv->async_context);
	g_tls_connection_handshake_async (G_TLS_CONNECTION (priv->conn),
					  G_PRIORITY_DEFAULT,
					  cancellable, handshake_async_ready,
					  data);
}
