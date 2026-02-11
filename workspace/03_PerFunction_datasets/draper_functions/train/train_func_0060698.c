g_dbus_remove_all_watches(DBusConnection *connection)
{
	struct filter_data *data;

	while ((data = filter_data_find(connection))) {
		listeners = g_slist_remove(listeners, data);
		filter_data_call_and_free(data);
	}

	dbus_connection_remove_filter(connection, message_filter, NULL);
}
