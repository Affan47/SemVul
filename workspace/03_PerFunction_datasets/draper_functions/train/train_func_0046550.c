nm_gconf_set_mac_address_helper (GConfClient *client,
                                 const char *path,
                                 const char *key,
                                 const char *setting,
                                 GByteArray *value)
{
	char *gc_key;
	MacAddressKey *tmp = &mac_keys[0];
	gboolean found = FALSE;
	char *str;

	g_return_val_if_fail (path != NULL, FALSE);
	g_return_val_if_fail (key != NULL, FALSE);
	g_return_val_if_fail (setting != NULL, FALSE);


	while (tmp->setting_name) {
		if (!strcmp (tmp->setting_name, setting) && !strcmp (tmp->key_name, key)) {
			found = TRUE;
			break;
		}
		tmp++;
	}
	if (!found || !value)
		return FALSE;

	g_return_val_if_fail (value->len == ETH_ALEN, FALSE);

	gc_key = g_strdup_printf ("%s/%s/%s", path, setting, key);
	if (!gc_key) {
		g_warning ("Not enough memory to create gconf path");
		return FALSE;
	}

	str = g_strdup_printf ("%02X:%02X:%02X:%02X:%02X:%02X",
	                       value->data[0], value->data[1], value->data[2],
	                       value->data[3], value->data[4], value->data[5]);
	gconf_client_set_string (client, gc_key, str, NULL);
	g_free (str);

	g_free (gc_key);
	return TRUE;
}
