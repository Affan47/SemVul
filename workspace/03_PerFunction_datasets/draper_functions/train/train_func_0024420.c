check_devices_mcl(void)
{
	struct hdp_device *dev;
	GSList *l, *to_delete = NULL;

	for (l = devices; l; l = l->next) {
		dev = l->data;
		device_unref_mcl(dev);

		if (!dev->sdp_present)
			to_delete = g_slist_append(to_delete, dev);
		else
			remove_channels(dev);
	}

	for (l = to_delete; l; l = l->next) {
		const char *path;

		path = device_get_path(dev->dev);
		g_dbus_unregister_interface(dev->conn, path, HEALTH_DEVICE);
	}

	g_slist_free(to_delete);
}
