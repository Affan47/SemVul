nm_ce_service_new (DBusGConnection *bus, DBusGProxy *proxy, NMConnectionList *list)
{
	GObject *object;
	DBusConnection *connection;
	GError *err = NULL;
	guint32 result;

	g_return_val_if_fail (bus != NULL, NULL);
	g_return_val_if_fail (proxy != NULL, NULL);

	object = g_object_new (NM_TYPE_CE_SERVICE, NULL);
	if (!object)
		return NULL;

	NM_CE_SERVICE (object)->list = list;

	dbus_connection_set_change_sigpipe (TRUE);
	connection = dbus_g_connection_get_connection (bus);
	dbus_connection_set_exit_on_disconnect (connection, FALSE);


	if (!dbus_g_proxy_call (proxy, "RequestName", &err,
	                        G_TYPE_STRING, NM_CE_DBUS_SERVICE_NAME,
	                        G_TYPE_UINT, DBUS_NAME_FLAG_DO_NOT_QUEUE,
	                        G_TYPE_INVALID,
	                        G_TYPE_UINT, &result,
	                        G_TYPE_INVALID)) {
		g_warning ("Could not acquire the connection editor service.\n"
		           "  Message: '%s'", err->message);
		g_error_free (err);
		return (NMCEService *) object;
	}

	if (result == DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {

		dbus_g_connection_register_g_object (bus, "/", object);
	}

	return (NMCEService *) object;
}
