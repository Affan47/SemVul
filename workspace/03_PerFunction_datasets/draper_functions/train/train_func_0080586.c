device_removed (const char *bdaddr)
{
	GSettings *settings;
	char *str;

	if (has_geoclue_settings () == FALSE)
		return;

	settings = g_settings_new (GPS_ID);

	str = g_settings_get_string (settings, GPS_KEY);
	if (g_strcmp0 (str, bdaddr) == 0) {
		g_settings_set_string (settings, GPS_KEY, "");
		g_debug ("Device '%s' got disabled as a Geoclue GPS", bdaddr);
	}

	g_free (str);
	g_object_unref (settings);
}
