disable_intermediate(DBusConnection *conn, DBusMessage *msg,
								void *data)
{
	const char *sender = dbus_message_get_sender(msg);
	struct thermometer *t = data;
	struct watcher *watcher;
	char *path;

	if (!dbus_message_get_args(msg, NULL, DBUS_TYPE_OBJECT_PATH, &path,
							DBUS_TYPE_INVALID))
		return btd_error_invalid_args(msg);

	watcher = find_watcher(t->iwatchers, sender, path);
	if (watcher == NULL)
		return btd_error_does_not_exist(msg);

	DBG("Intermediate measurement %s unregistered", path);

	remove_int_watcher(t, watcher);

	return dbus_message_new_method_return(msg);
}
