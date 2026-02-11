serial_port_free(void *data)
{
	struct serial_port *port = data;
	struct serial_device *device = port->device;

	if (device && port->listener_id > 0)
		g_dbus_remove_watch(device->conn, port->listener_id);

	port_release(port);

	g_free(port->uuid);
	g_free(port);
}
