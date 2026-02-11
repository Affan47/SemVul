DBUS_unregister(DBusConnection *connection, const char *name)
{
	DBusError error;
	int ret, socket;

	dbus_error_init(&error);

	ret = dbus_bus_release_name(connection, name, &error);

	if (dbus_error_is_set(&error))
	{
		GB.Error("Unable to unregister application name");
		dbus_error_free(&error);
		return TRUE;
	}

	return DBUS_watch(connection, FALSE);
}
