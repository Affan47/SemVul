destroy_device(struct modem_data *modem)
{
	DBG("%s", modem->path);

	connman_device_set_powered(modem->device, FALSE);

	if (modem->network != NULL) {
		connman_device_remove_network(modem->device, modem->network);
		connman_network_unref(modem->network);
		modem->network = NULL;
	}

	connman_device_unregister(modem->device);
	connman_device_unref(modem->device);

	modem->device = NULL;
}
