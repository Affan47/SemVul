get_connection(void)
{
	GError *error = NULL;
	DBusGConnection *conn;

	conn = dbus_g_bus_get_private(DBUS_BUS_SYSTEM, NULL, &error);

	if (error)
	{
		g_error_free(error);
		error = NULL;

		conn = dbus_g_connection_open("unix:abstract=/com/ubuntu/upstart",
			&error);

		if (error)
		{
			g_warning("Can't connect to either system or Upstart "
				"DBus bus.");
			g_error_free(error);

			return NULL;
		}
	}

	return conn;
}
