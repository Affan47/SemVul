create_device_internal(DBusConnection *conn,
						struct btd_adapter *adapter,
						const char *address, int *err)
{
	struct remote_dev_info *dev;
	struct btd_device *device;
	bdaddr_t addr;
	uint8_t bdaddr_type;

	str2ba(address, &addr);

	dev = adapter_search_found_devices(adapter, &addr);
	if (dev)
		bdaddr_type = dev->bdaddr_type;
	else
		bdaddr_type = BDADDR_BREDR;

	device = adapter_create_device(conn, adapter, address, bdaddr_type);
	if (!device && err)
		*err = -ENOMEM;

	return device;
}
