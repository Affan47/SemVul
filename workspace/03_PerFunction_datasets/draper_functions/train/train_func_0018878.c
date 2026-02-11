cm_tdbus_dispatch_status(DBusConnection *conn, DBusDispatchStatus new_status,
			 void *data)
{
	while (new_status == DBUS_DISPATCH_DATA_REMAINS) {
		new_status = dbus_connection_dispatch(conn);
	}
}
