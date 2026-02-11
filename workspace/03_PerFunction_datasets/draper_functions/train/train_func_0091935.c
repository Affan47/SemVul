update_wireless_setting_from_if_block(NMConnection *connection,
							   if_block *block)
{
	gint wpa_l= strlen("wpa-");
	gint wireless_l= strlen("wireless-");

	if_data *curr = block->info;
	const gchar* value = ifparser_getkey (block, "inet");
	struct _Mapping mapping[] = {
		{"ssid", "ssid"},
		{ NULL, NULL}
	};

	NMSettingWireless *wireless_setting = NULL;

	if(value && !strcmp("ppp", value)) {
		return;
	}

	PLUGIN_PRINT ("SCPlugin-Ifupdown", "update wireless settings (%s).", block->name);
	wireless_setting = NM_SETTING_WIRELESS(nm_setting_wireless_new());

	while(curr) {
		if(strlen(curr->key) > wireless_l &&
		   !strncmp("wireless-", curr->key, wireless_l)) {
			const gchar* newkey = map_by_mapping(mapping, curr->key+wireless_l);
			PLUGIN_PRINT ("SCPlugin-Ifupdown", "wireless setting key: %s='%s'",
					    newkey, curr->data);
			if(newkey && !strcmp("ssid", newkey)) {
				GByteArray *ssid;
				gint len = strlen(curr->data);

				ssid = g_byte_array_sized_new (len);
				g_byte_array_append (ssid, (const guint8 *) curr->data, len);
				g_object_set (wireless_setting, NM_SETTING_WIRELESS_SSID, ssid, NULL);
				g_byte_array_free (ssid, TRUE);
				PLUGIN_PRINT("SCPlugin-Ifupdown", "setting wireless ssid = %d", len);
			} else {
				g_object_set(wireless_setting,
					   newkey, curr->data,
					   NULL);
			}
		} else if(strlen(curr->key) > wpa_l &&
				!strncmp("wpa-", curr->key, wpa_l)) {
			const gchar* newkey = map_by_mapping(mapping, curr->key+wpa_l);

			if(newkey && !strcmp("ssid", newkey)) {
				GByteArray *ssid;
				gint len = strlen(curr->data);

				ssid = g_byte_array_sized_new (len);
				g_byte_array_append (ssid, (const guint8 *) curr->data, len);
				g_object_set (wireless_setting, NM_SETTING_WIRELESS_SSID, ssid, NULL);
				g_byte_array_free (ssid, TRUE);
				PLUGIN_PRINT("SCPlugin-Ifupdown", "setting wpa ssid = %d", len);
			} else if(newkey) {

				g_object_set(wireless_setting,
						   newkey, curr->data,
						   NULL);
				PLUGIN_PRINT ("SCPlugin-Ifupdown", "setting wpa newkey(%s)=data(%s)", newkey, curr->data);
			}
		}
		curr = curr->next;
	}
	nm_connection_add_setting(connection, (NMSetting*) wireless_setting);
}
