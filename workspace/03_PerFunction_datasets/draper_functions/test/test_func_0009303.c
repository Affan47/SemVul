modem_enable(struct connman_device *device)
{
	struct modem_data *modem = connman_device_get_data(device);

	DBG("%s device %p", modem->path, device);

	if (modem->online == TRUE)
		return 0;

	return modem_set_online(modem, TRUE);
}
