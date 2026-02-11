socket_connect_result (SoupSocket *sock, guint status, gpointer user_data)
{
	SoupConnectionAsyncConnectData *data = user_data;
	SoupConnectionPrivate *priv = SOUP_CONNECTION_GET_PRIVATE (data->conn);

	if (!SOUP_STATUS_IS_SUCCESSFUL (status)) {
		socket_connect_finished (sock, status, data);
		return;
	}

	priv->proxy_uri = soup_socket_get_http_proxy_uri (priv->socket);

	if (priv->ssl && !priv->proxy_uri) {
		if (soup_socket_start_ssl (sock, data->cancellable)) {
			soup_connection_event (data->conn,
					       G_SOCKET_CLIENT_TLS_HANDSHAKING,
					       NULL);
			soup_socket_handshake_async (sock, data->cancellable,
						     socket_connect_finished, data);
			return;
		}

		status = SOUP_STATUS_SSL_FAILED;
	}

	socket_connect_finished (sock, status, data);
}
