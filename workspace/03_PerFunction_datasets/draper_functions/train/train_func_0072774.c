source_authentication_update_connectable (ESourceAuthentication *extension)
{
	const gchar *host;
	guint16 port;


	g_clear_object (&extension->priv->connectable);

	host = e_source_authentication_get_host (extension);
	port = e_source_authentication_get_port (extension);

	if (host != NULL) {
		GSocketConnectable *connectable;
		connectable = g_network_address_new (host, port);
		extension->priv->connectable = connectable;
	}
}
