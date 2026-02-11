nm_is_running (void)
{
	DBusConnection *bus;
	DBusError error;
	gboolean running = FALSE;

	dbus_error_init (&error);
	bus = dbus_bus_get (DBUS_BUS_SYSTEM, &error);
	if (dbus_error_is_set (&error)) {
		g_message (_("Bluetooth configuration not possible (failed to connect to D-Bus: (%s) %s)."),
		           error.name, error.message);
		dbus_error_free (&error);
		return FALSE;
	}

	dbus_error_init (&error);
	running = dbus_bus_name_has_owner (bus, NM_DBUS_SERVICE, &error);
	if (dbus_error_is_set (&error)) {
		g_message (_("Bluetooth configuration not possible (error finding NetworkManager: (%s) %s)."),
		           error.name, error.message);
	}

	dbus_connection_unref (bus);
	return running;
}
