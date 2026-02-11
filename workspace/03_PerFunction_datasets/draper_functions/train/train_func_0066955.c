egg_dbus_monitor_assign (EggDbusMonitor *monitor, EggDbusMonitorType bus_type, const gchar *service)
{
	GError *error = NULL;
	gboolean connected;
	DBusConnection *conn;

	g_return_val_if_fail (EGG_IS_DBUS_MONITOR (monitor), FALSE);
	g_return_val_if_fail (service != NULL, FALSE);

	if (monitor->priv->proxy != NULL) {
		g_warning ("already assigned!");
		return FALSE;
	}

	monitor->priv->service = g_strdup (service);
	monitor->priv->bus_type = bus_type;


	if (bus_type == EGG_DBUS_MONITOR_SESSION)
		monitor->priv->connection = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
	else
		monitor->priv->connection = dbus_g_bus_get (DBUS_BUS_SYSTEM, &error);
	if (error != NULL) {
		g_warning ("Cannot connect to bus: %s", error->message);
		g_error_free (error);
		return FALSE;
	}
	monitor->priv->proxy = dbus_g_proxy_new_for_name_owner (monitor->priv->connection,
								DBUS_SERVICE_DBUS,
								DBUS_PATH_DBUS,
						 		DBUS_INTERFACE_DBUS,
								&error);
	if (error != NULL) {
		g_warning ("Cannot connect to DBUS: %s", error->message);
		g_error_free (error);
		return FALSE;
	}
	dbus_g_proxy_add_signal (monitor->priv->proxy, "NameOwnerChanged",
				 G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID);
	dbus_g_proxy_connect_signal (monitor->priv->proxy, "NameOwnerChanged",
				     G_CALLBACK (egg_dbus_monitor_name_owner_changed_cb),
				     monitor, NULL);


	connected = egg_dbus_monitor_is_connected (monitor);
	if (connected)
		g_signal_emit (monitor, signals [EGG_DBUS_MONITOR_CONNECTION_CHANGED], 0, TRUE);


	conn = dbus_g_connection_get_connection (monitor->priv->connection);
	monitor->priv->unique_name = dbus_bus_get_unique_name (conn);
	return TRUE;
}
