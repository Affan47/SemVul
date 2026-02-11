urf_client_device_added (UrfClient   *client,
			 const gchar *object_path)
{
	UrfDevice *device;

	device = urf_client_find_device (client, object_path);
	if (device != NULL) {
		g_warning ("already added: %s", object_path);
		return;
	}

	device = urf_client_add (client, object_path);

	g_signal_emit (client, signals [URF_CLIENT_DEVICE_ADDED], 0, device);
}
