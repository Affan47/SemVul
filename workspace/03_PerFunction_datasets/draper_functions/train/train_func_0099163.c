server_create_notify(DBusGProxy *proxy, DBusGProxyCall *call, gpointer data)
{
	GError *error = NULL;
	const char *path = NULL;

	DEBUG(GYPSY_SERVER": Create: Notify");

	dbus_g_proxy_end_call(proxy, call, &error,
		DBUS_TYPE_G_OBJECT_PATH, &path,
		G_TYPE_INVALID);

	if (error) {
		WARNING(GYPSY_SERVER": Create: %s", error->message);
		g_error_free(error);
		gypsy_device_create_failed = TRUE;
		gypsy_device_path = NULL;
	} else {
		DEBUG(GYPSY_SERVER": Create: OK: %s", path);
		gypsy_device_create_failed = FALSE;
		gypsy_device_path = g_strdup(path);

		if (client_list || nowait) {
			device_start();
		}
	}
}
