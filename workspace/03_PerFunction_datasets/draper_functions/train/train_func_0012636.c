create_stored_device_from_blocked(char *key, char *value,
							void *user_data)
{
	struct btd_adapter *adapter = user_data;
	struct btd_device *device;

	if (g_slist_find_custom(adapter->devices,
				key, (GCompareFunc) device_address_cmp))
		return;

	device = device_create(connection, adapter, key, BDADDR_BREDR);
	if (device) {
		device_set_temporary(device, FALSE);
		adapter->devices = g_slist_append(adapter->devices, device);
	}
}
