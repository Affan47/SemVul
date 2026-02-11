hdp_device_unregister(struct btd_device *device)
{
	struct hdp_device *hdp_dev;
	const char *path;
	GSList *l;

	l = g_slist_find_custom(devices, device, cmp_device);
	if (l == NULL)
		return;

	hdp_dev = l->data;
	path = device_get_path(hdp_dev->dev);
	g_dbus_unregister_interface(hdp_dev->conn, path, HEALTH_DEVICE);
}
