up_backend_coldplug (UpBackend *backend, UpDaemon *daemon)
{
	GUdevDevice *native;
	GList *devices;
	GList *l;
	guint i;
	gboolean ret;
	const gchar *subsystems_wup[] = {"power_supply", "usb", "usbmisc", "tty", "input", "hid", NULL};
	const gchar *subsystems[] = {"power_supply", "usb", "usbmisc", "input", "hid", NULL};

	backend->priv->daemon = g_object_ref (daemon);
	backend->priv->device_list = up_daemon_get_device_list (daemon);
	if (up_config_get_boolean (backend->priv->config, "EnableWattsUpPro"))
		backend->priv->gudev_client = g_udev_client_new (subsystems_wup);
	else
		backend->priv->gudev_client = g_udev_client_new (subsystems);
	g_signal_connect (backend->priv->gudev_client, "uevent",
			  G_CALLBACK (up_backend_uevent_signal_handler_cb), backend);


	for (i=0; subsystems[i] != NULL; i++) {
		g_debug ("registering subsystem : %s", subsystems[i]);
		devices = g_udev_client_query_by_subsystem (backend->priv->gudev_client, subsystems[i]);
		for (l = devices; l != NULL; l = l->next) {
			native = l->data;
			up_backend_device_add (backend, native);
		}
		g_list_foreach (devices, (GFunc) g_object_unref, NULL);
		g_list_free (devices);
	}


	backend->priv->dock = up_dock_new ();
	ret = up_config_get_boolean (backend->priv->config, "PollDockDevices");
	g_debug ("Polling docks: %s", ret ? "YES" : "NO");
	up_dock_set_should_poll (backend->priv->dock, ret);
	ret = up_dock_coldplug (backend->priv->dock, daemon);
	if (!ret)
		g_warning ("failed to coldplug dock devices");

	return TRUE;
}
