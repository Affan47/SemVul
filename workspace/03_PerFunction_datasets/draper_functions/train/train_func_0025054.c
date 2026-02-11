connman_setting_get_bool(const char *key)
{
	if (g_str_equal(key, CONF_BG_SCAN) == TRUE)
		return connman_settings.bg_scan;

	if (g_str_equal(key, CONF_ALLOW_HOSTNAME_UPDATES) == TRUE)
		return connman_settings.allow_hostname_updates;

	if (g_str_equal(key, CONF_SINGLE_TECH) == TRUE)
		return connman_settings.single_tech;

	if (g_str_equal(key, CONF_PERSISTENT_TETHERING_MODE) == TRUE)
		return connman_settings.persistent_tethering_mode;

	return FALSE;
}
