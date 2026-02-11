g_dbus_add_properties_watch(DBusConnection *connection,
				const char *sender, const char *path,
				const char *interface,
				GDBusSignalFunction function, void *user_data,
				GDBusDestroyFunction destroy)
{
	struct filter_data *data;
	struct filter_callback *cb;

	data = filter_data_get(connection, signal_filter, sender, path,
				DBUS_INTERFACE_PROPERTIES, "PropertiesChanged",
				interface);
	if (data == NULL)
		return 0;

	cb = filter_data_add_callback(data, NULL, NULL, function, destroy,
					user_data);
	if (cb == NULL)
		return 0;

	if (data->name != NULL && data->name_watch == 0)
		data->name_watch = g_dbus_add_service_watch(connection,
							data->name, NULL,
							NULL, NULL, NULL);

	return cb->id;
}
