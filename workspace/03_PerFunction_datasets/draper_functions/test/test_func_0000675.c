network_probe(struct btd_device *device, GSList *uuids, uint16_t id)
{
	struct btd_adapter *adapter = device_get_adapter(device);
	const gchar *path = device_get_path(device);
	bdaddr_t src, dst;

	DBG("path %s", path);

	adapter_get_address(adapter, &src);
	device_get_address(device, &dst, NULL);

	return connection_register(device, path, &src, &dst, id);
}
