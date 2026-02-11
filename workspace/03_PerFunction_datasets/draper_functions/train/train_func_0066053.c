session_filter(DBusConnection *conn,
						DBusMessage *msg, void *data)
{
	const char *name, *old, *new;

	if (dbus_message_is_signal(msg, DBUS_INTERFACE_PROPERTIES,
						"PropertiesChanged"))
		return properties_changed(conn, msg);

	if (!dbus_message_is_signal(msg, DBUS_INTERFACE_DBUS,
						"NameOwnerChanged"))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (!dbus_message_get_args(msg, NULL,
					DBUS_TYPE_STRING, &name,
					DBUS_TYPE_STRING, &old,
					DBUS_TYPE_STRING, &new,
					DBUS_TYPE_INVALID)) {
		fprintf(stderr, "Invalid arguments for NameOwnerChanged signal");
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	if (!g_str_has_prefix(name, "org.mpris"))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (*new == '\0') {
		printf("player %s at %s disappear\n", name, old);
		remove_player(conn, old);
	} else {
		printf("player %s at %s found\n", name, new);
		add_player(conn, name, new);
	}

	return DBUS_HANDLER_RESULT_HANDLED;
}
