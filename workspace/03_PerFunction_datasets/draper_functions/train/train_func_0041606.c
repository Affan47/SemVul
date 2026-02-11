connman_network_get_bool(struct connman_network *network,
							const char *key)
{
	DBG("network %p key %s", network, key);

	if (g_str_equal(key, "Roaming") == TRUE)
		return network->roaming;
	else if (g_str_equal(key, "WiFi.WPS") == TRUE)
		return network->wifi.wps;
	else if (g_str_equal(key, "WiFi.UseWPS") == TRUE)
		return network->wifi.use_wps;

	return FALSE;
}
