connman_device_disconnect_service(struct connman_device *device)
{
	DBG("device %p", device);

	device->reconnect = FALSE;

	if (device->network) {
		struct connman_service *service =
			connman_service_lookup_from_network(device->network);

		if (service != NULL)
			__connman_service_disconnect(service);
		else
			connman_network_set_connected(device->network, FALSE);
	}

	return 0;
}
