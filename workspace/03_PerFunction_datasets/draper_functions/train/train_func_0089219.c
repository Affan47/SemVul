remove_player(DBusConnection *conn, const char *sender)
{
	DBusMessage *msg;
	char *path;

	msg = dbus_message_new_method_call("org.bluez", adapter,
					"org.bluez.Media",
					"UnregisterPlayer");
	if (!msg) {
		fprintf(stderr, "Can't allocate new method call\n");
		return;
	}

	path = sender2path(sender);
	dbus_message_append_args(msg, DBUS_TYPE_OBJECT_PATH, &path,
					DBUS_TYPE_INVALID);

	dbus_connection_send(sys, msg, NULL);

	dbus_message_unref(msg);
	g_free(path);
}
