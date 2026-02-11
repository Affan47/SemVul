soup_server_constructor (GType                  type,
			 guint                  n_construct_properties,
			 GObjectConstructParam *construct_properties)
{
	GObject *server;
	SoupServerPrivate *priv;

	server = G_OBJECT_CLASS (soup_server_parent_class)->constructor (
		type, n_construct_properties, construct_properties);
	if (!server)
		return NULL;
	priv = SOUP_SERVER_GET_PRIVATE (server);

	if (!priv->iface) {
		priv->iface =
			soup_address_new_any (SOUP_ADDRESS_FAMILY_IPV4,
					      priv->port);
	}

	if (priv->ssl_cert_file && priv->ssl_key_file) {
		GError *error = NULL;

		if (priv->ssl_cert)
			g_object_unref (priv->ssl_cert);
		priv->ssl_cert = g_tls_certificate_new_from_files (priv->ssl_cert_file, priv->ssl_key_file, &error);
		if (!priv->ssl_cert) {
			g_warning ("Could not read SSL certificate from '%s': %s",
				   priv->ssl_cert_file, error->message);
			g_error_free (error);
			g_object_unref (server);
			return NULL;
		}
	}

	priv->listen_sock =
		soup_socket_new (SOUP_SOCKET_LOCAL_ADDRESS, priv->iface,
				 SOUP_SOCKET_SSL_CREDENTIALS, priv->ssl_cert,
				 SOUP_SOCKET_ASYNC_CONTEXT, priv->async_context,
				 NULL);
	if (!soup_socket_listen (priv->listen_sock)) {
		g_object_unref (server);
		return NULL;
	}


	g_object_unref (priv->iface);
	priv->iface = soup_socket_get_local_address (priv->listen_sock);
	g_object_ref (priv->iface);
	priv->port = soup_address_get_port (priv->iface);

	return server;
}
