on_proxy_appeared (GObject      *source_object,
		   GAsyncResult *res,
		   gpointer      user_data)
{
	GSimpleAsyncResult   *result = G_SIMPLE_ASYNC_RESULT (user_data);
	PanelAppletContainer *container;
	GDBusProxy           *proxy;
	GError               *error = NULL;

	proxy = g_dbus_proxy_new_finish (res, &error);
	if (!proxy) {
		g_simple_async_result_set_from_error (result, error);
		g_error_free (error);
		g_simple_async_result_complete (result);
		g_object_unref (result);

		return;
	}

	container = PANEL_APPLET_CONTAINER (g_async_result_get_source_object (G_ASYNC_RESULT (result)));

	container->priv->applet_proxy = proxy;
	g_signal_connect (container->priv->applet_proxy, "g-signal",
			  G_CALLBACK (panel_applet_container_child_signal),
			  container);
	g_dbus_connection_signal_subscribe (g_dbus_proxy_get_connection (proxy),
					    g_dbus_proxy_get_name (proxy),
					    "org.freedesktop.DBus.Properties",
					    "PropertiesChanged",
					    g_dbus_proxy_get_object_path (proxy),
					    PANEL_APPLET_INTERFACE,
					    G_DBUS_SIGNAL_FLAGS_NONE,
					    (GDBusSignalCallback) on_property_changed,
					    container, NULL);

	g_simple_async_result_complete (result);
	g_object_unref (result);

	if (container->priv->xid > 0) {
		gtk_socket_add_id (GTK_SOCKET (container->priv->socket),
				   container->priv->xid);
	}


	g_object_unref (container);
}
