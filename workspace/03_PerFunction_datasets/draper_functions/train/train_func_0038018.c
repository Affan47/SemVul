g_dbus_detach_object_manager(DBusConnection *connection)
{
	if (!g_dbus_unregister_interface(connection, "/",
					DBUS_INTERFACE_OBJECT_MANAGER))
		return FALSE;

	root = NULL;

	return TRUE;
}
