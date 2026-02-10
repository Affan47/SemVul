cd_sensor_client_remove (CdSensorClient *sensor_client,
			 GUdevDevice *device)
{
	CdSensor *sensor;
	const gchar *device_file;
	const gchar *device_path;
	const gchar *tmp;
	guint i;


	tmp = g_udev_device_get_property (device, "COLORD_SENSOR_KIND");
	if (tmp == NULL)
		goto out;


	device_file = g_udev_device_get_device_file (device);
	if (device_file == NULL)
		goto out;


	device_path = g_udev_device_get_sysfs_path (device);
	g_debug ("removing color management device: %s [%s]",
		 device_path, device_file);
	for (i = 0; i < sensor_client->priv->array_sensors->len; i++) {
		sensor = g_ptr_array_index (sensor_client->priv->array_sensors, i);
		if (g_strcmp0 (cd_sensor_get_device_path (sensor), device_path) == 0) {
			g_debug ("emit: removed");
			g_signal_emit (sensor_client, signals[SIGNAL_SENSOR_REMOVED], 0, sensor);
			g_ptr_array_remove_index_fast (sensor_client->priv->array_sensors, i);
			goto out;
		}
	}


	g_warning ("removed CM sensor that was never added");
out:
	return;
}
