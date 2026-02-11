merge_network(struct supplicant_network *network)
{
	GString *str;
	const char *ssid, *mode, *key_mgmt;
	unsigned int i, ssid_len;
	char *group;

	ssid = g_hash_table_lookup(network->config_table, "ssid");
	mode = g_hash_table_lookup(network->config_table, "mode");
	key_mgmt = g_hash_table_lookup(network->config_table, "key_mgmt");

	DBG("ssid %s mode %s", ssid, mode);

	if (ssid != NULL)
		ssid_len = strlen(ssid);
	else
		ssid_len = 0;

	str = g_string_sized_new((ssid_len * 2) + 24);
	if (str == NULL)
		return;

	for (i = 0; i < ssid_len; i++)
		g_string_append_printf(str, "%02x", ssid[i]);

	if (g_strcmp0(mode, "0") == 0)
		g_string_append_printf(str, "_infra");
	else if (g_strcmp0(mode, "1") == 0)
		g_string_append_printf(str, "_adhoc");

	if (g_strcmp0(key_mgmt, "WPA-PSK") == 0)
		g_string_append_printf(str, "_psk");

	group = g_string_free(str, FALSE);

	DBG("%s", group);

	g_free(group);

	g_hash_table_destroy(network->config_table);

	g_free(network->path);
	g_free(network);
}
