networking_set_sleep (NmCli *nmc, gboolean in_sleep)
{
	DBusGConnection *connection = NULL;
	DBusGProxy *proxy = NULL;
	GError *err = NULL;

	connection = dbus_g_bus_get (DBUS_BUS_SYSTEM, &err);
	if (!connection) {
		g_string_printf (nmc->return_text, _("Error: Couldn't connect to system bus: %s"), err->message);
		nmc->return_value = NMC_RESULT_ERROR_UNKNOWN;
		g_error_free (err);
		goto gone;
	}

	proxy = dbus_g_proxy_new_for_name (connection,
	                                   "org.freedesktop.NetworkManager",
	                                   "/org/freedesktop/NetworkManager",
	                                   "org.freedesktop.NetworkManager");
	if (!proxy) {
		g_string_printf (nmc->return_text, _("Error: Couldn't create D-Bus object proxy."));
		nmc->return_value = NMC_RESULT_ERROR_UNKNOWN;
		goto gone;
	}

	if (!dbus_g_proxy_call (proxy, "Sleep", &err, G_TYPE_BOOLEAN, in_sleep, G_TYPE_INVALID, G_TYPE_INVALID)) {
		g_string_printf (nmc->return_text, _("Error in sleep: %s"), err->message);
		nmc->return_value = NMC_RESULT_ERROR_UNKNOWN;
		g_error_free (err);
	}

gone:
	if (connection) dbus_g_connection_unref (connection);
	if (proxy) g_object_unref (proxy);
}
