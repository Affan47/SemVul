port_disconnect(DBusConnection *conn,
					DBusMessage *msg, void *user_data)
{
	struct serial_device *device = user_data;
	struct serial_port *port;
	const char *dev, *owner, *caller;

	if (dbus_message_get_args(msg, NULL, DBUS_TYPE_STRING, &dev,
						DBUS_TYPE_INVALID) == FALSE)
		return NULL;

	port = find_port(device->ports, dev);
	if (!port)
		return btd_error_does_not_exist(msg);

	if (!port->listener_id)
		return btd_error_not_connected(msg);

	owner = dbus_message_get_sender(port->msg);
	caller = dbus_message_get_sender(msg);
	if (!g_str_equal(owner, caller))
		return btd_error_not_authorized(msg);

	port_release(port);

	g_dbus_remove_watch(conn, port->listener_id);
	port->listener_id = 0;

	return g_dbus_create_reply(msg, DBUS_TYPE_INVALID);
}
