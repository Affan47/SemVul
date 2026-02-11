dispatch_dbus(void)
{
    if (sessconn != NULL && dbus_connection_get_dispatch_status(sessconn) == DBUS_DISPATCH_DATA_REMAINS) {
	while (DBUS_DISPATCH_DATA_REMAINS == dbus_connection_dispatch(sessconn));
    }
    if (sysconn != NULL && dbus_connection_get_dispatch_status(sysconn) == DBUS_DISPATCH_DATA_REMAINS) {
	while (DBUS_DISPATCH_DATA_REMAINS == dbus_connection_dispatch(sysconn));
    }
}
