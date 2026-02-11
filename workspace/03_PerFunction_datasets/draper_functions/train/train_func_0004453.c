up_device_wup_refresh (UpDevice *device)
{
	gboolean ret = FALSE;
	GTimeVal timeval;
	gchar *data = NULL;
	UpDeviceWup *wup = UP_DEVICE_WUP (device);


	data = up_device_wup_read_command (wup);
	if (data == NULL) {
		g_debug ("no data");
		goto out;
	}


	ret = up_device_wup_parse_command (wup, data);
	if (!ret) {
		g_debug ("failed to parse %s", data);
		goto out;
	}


	g_get_current_time (&timeval);
	g_object_set (device, "update-time", (guint64) timeval.tv_sec, NULL);

out:
	g_free (data);

	return TRUE;
}
