device_unblock(DBusConnection *conn, struct btd_device *device,
				gboolean silent, gboolean update_only)
{
	int err = 0;
	bdaddr_t src;

	if (!device->blocked)
		return 0;

	if (!update_only)
		err = btd_adapter_unblock_address(device->adapter,
					&device->bdaddr, device->bdaddr_type);

	if (err < 0)
		return err;

	device->blocked = FALSE;

	adapter_get_address(device->adapter, &src);

	err = write_blocked(&src, &device->bdaddr, FALSE);
	if (err < 0)
		error("write_blocked(): %s (%d)", strerror(-err), -err);

	if (!silent) {
		emit_property_changed(conn, device->path,
					DEVICE_INTERFACE, "Blocked",
					DBUS_TYPE_BOOLEAN, &device->blocked);
		device_probe_drivers(device, device->uuids);
	}

	return 0;
}
