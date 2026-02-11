soup_socket_finalize (GObject *object)
{
	SoupSocketPrivate *priv = SOUP_SOCKET_GET_PRIVATE (object);

	if (priv->connect_cancel) {
		if (priv->clean_dispose)
			g_warning ("Disposing socket %p during connect", object);
		g_object_unref (priv->connect_cancel);
	}
	if (priv->gsock) {
		if (priv->clean_dispose)
			g_warning ("Disposing socket %p while still connected", object);
		disconnect_internal (SOUP_SOCKET (object), TRUE);
	}

	g_clear_object (&priv->conn);
	g_clear_object (&priv->iostream);
	g_clear_object (&priv->istream);
	g_clear_object (&priv->ostream);

	g_clear_object (&priv->local_addr);
	g_clear_object (&priv->remote_addr);

	g_clear_object (&priv->proxy_resolver);

	if (priv->watch_src) {
		if (priv->clean_dispose && !priv->is_server)
			g_warning ("Disposing socket %p during async op", object);
		g_source_destroy (priv->watch_src);
	}
	g_clear_pointer (&priv->async_context, g_main_context_unref);

	g_mutex_clear (&priv->addrlock);
	g_mutex_clear (&priv->iolock);

	G_OBJECT_CLASS (soup_socket_parent_class)->finalize (object);
}
