create_device(struct modem_data *modem)
{
	struct connman_device *device;
	char *ident = NULL;

	DBG("%s", modem->path);

	if (modem->imsi != NULL)
		ident = modem->imsi;
	else if (modem->serial != NULL)
		ident = modem->serial;

	if (connman_dbus_validate_ident(ident) == FALSE)
		ident = connman_dbus_encode_string(ident);
	else
		ident = g_strdup(ident);

	device = connman_device_create("ofono", CONNMAN_DEVICE_TYPE_CELLULAR);
	if (device == NULL)
		goto out;

	DBG("device %p", device);

	connman_device_set_ident(device, ident);

	connman_device_set_string(device, "Path", modem->path);

	connman_device_set_data(device, modem);

	if (connman_device_register(device) < 0) {
		connman_error("Failed to register cellular device");
		connman_device_unref(device);
		goto out;
	}

	modem->device = device;

	connman_device_set_powered(modem->device, modem->online);
out:
	g_free(ident);
}
