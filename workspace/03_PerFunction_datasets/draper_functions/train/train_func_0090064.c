backend_update_online_state_idle_cb (gpointer user_data)
{
	EBackend *backend;
	GSocketConnectable *connectable;
	GCancellable *cancellable;

	backend = E_BACKEND (user_data);
	connectable = e_backend_ref_connectable (backend);

	g_mutex_lock (&backend->priv->update_online_state_lock);
	g_source_unref (backend->priv->update_online_state);
	backend->priv->update_online_state = NULL;
	g_mutex_unlock (&backend->priv->update_online_state_lock);

	g_mutex_lock (&backend->priv->network_monitor_cancellable_lock);

	cancellable = backend->priv->network_monitor_cancellable;
	backend->priv->network_monitor_cancellable = NULL;

	if (cancellable != NULL) {
		g_cancellable_cancel (cancellable);
		g_object_unref (cancellable);
		cancellable = NULL;
	}

#if !GLIB_CHECK_VERSION (2, 35, 9)
	if (connectable && G_IS_NETWORK_ADDRESS (connectable)) {
		GNetworkAddress *network_address = G_NETWORK_ADDRESS (connectable);


		connectable = g_network_address_new (
			g_network_address_get_hostname (network_address),
			g_network_address_get_port (network_address));

		g_object_unref (network_address);
	}
#endif

	if (!connectable) {
		gchar *host = NULL;
		guint16 port = 0;

		if (e_backend_get_destination_address (backend, &host, &port) && host)
			connectable = g_network_address_new (host, port);

		g_free (host);
	}

	if (connectable == NULL) {
		e_backend_set_online (backend, TRUE);
	} else {
		cancellable = g_cancellable_new ();

		g_network_monitor_can_reach_async (
			backend->priv->network_monitor,
			connectable, cancellable,
			backend_network_monitor_can_reach_cb,
			g_object_ref (backend));
	}

	backend->priv->network_monitor_cancellable = cancellable;

	g_mutex_unlock (&backend->priv->network_monitor_cancellable_lock);

	if (connectable != NULL)
		g_object_unref (connectable);

	return FALSE;
}
