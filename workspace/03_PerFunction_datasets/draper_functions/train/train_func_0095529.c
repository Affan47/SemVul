dbus_connection_changed_cb (NMDBusManager *dbus_mgr,
                            DBusGConnection *connection,
                            gpointer user_data)
{
	NMBluezManager *self = NM_BLUEZ_MANAGER (user_data);

	if (!connection)
		bluez_cleanup (self, TRUE);
	else
		bluez_connect (self);
}
