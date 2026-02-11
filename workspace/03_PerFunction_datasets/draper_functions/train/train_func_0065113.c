device_removed(DBusConnection *conn, DBusMessage *message,
				void *user_data)
{
	const char *path;
	const char *signature = DBUS_TYPE_OBJECT_PATH_AS_STRING;

	if (dbus_message_has_signature(message, signature) == FALSE) {
		connman_error("dundee signature does not match");
		return TRUE;
	}

	dbus_message_get_args(message, NULL, DBUS_TYPE_OBJECT_PATH, &path,
				DBUS_TYPE_INVALID);
	remove_device(conn, path);
	return TRUE;
}
