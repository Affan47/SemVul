add_network_security_ciphers(DBusMessageIter *dict,
						GSupplicantSSID *ssid)
{
	unsigned int p_cipher, g_cipher, i;
	char *pairwise, *group;
	char *pair_ciphers[4];
	char *group_ciphers[5];

	p_cipher = ssid->pairwise_cipher;
	g_cipher = ssid->group_cipher;

	if (p_cipher == 0 && g_cipher == 0)
		return;

	i = 0;

	if (p_cipher & G_SUPPLICANT_PAIRWISE_CCMP)
		pair_ciphers[i++] = "CCMP";

	if (p_cipher & G_SUPPLICANT_PAIRWISE_TKIP)
		pair_ciphers[i++] = "TKIP";

	if (p_cipher & G_SUPPLICANT_PAIRWISE_NONE)
		pair_ciphers[i++] = "NONE";

	pair_ciphers[i] = NULL;

	i = 0;

	if (g_cipher & G_SUPPLICANT_GROUP_CCMP)
		group_ciphers[i++] = "CCMP";

	if (g_cipher & G_SUPPLICANT_GROUP_TKIP)
		group_ciphers[i++] = "TKIP";

	if (g_cipher & G_SUPPLICANT_GROUP_WEP104)
		group_ciphers[i++] = "WEP104";

	if (g_cipher & G_SUPPLICANT_GROUP_WEP40)
		group_ciphers[i++] = "WEP40";

	group_ciphers[i] = NULL;

	pairwise = g_strjoinv(" ", pair_ciphers);
	group = g_strjoinv(" ", group_ciphers);

	SUPPLICANT_DBG("cipher %s %s", pairwise, group);

	supplicant_dbus_dict_append_basic(dict, "pairwise",
						DBUS_TYPE_STRING,
						&pairwise);
	supplicant_dbus_dict_append_basic(dict, "group",
						DBUS_TYPE_STRING,
						&group);

	g_free(pairwise);
	g_free(group);
}
