add_network_security_wep(DBusMessageIter *dict,
					GSupplicantSSID *ssid)
{
	const char *auth_alg = "OPEN SHARED";
	const char *key_index = "0";

	supplicant_dbus_dict_append_basic(dict, "auth_alg",
					DBUS_TYPE_STRING, &auth_alg);

	if (ssid->passphrase) {
		int size = strlen(ssid->passphrase);
		if (size == 10 || size == 26) {
			unsigned char *key = g_try_malloc(13);
			char tmp[3];
			int i;

			memset(tmp, 0, sizeof(tmp));
			if (key == NULL)
				size = 0;

			for (i = 0; i < size / 2; i++) {
				memcpy(tmp, ssid->passphrase + (i * 2), 2);
				key[i] = (unsigned char) strtol(tmp, NULL, 16);
			}

			supplicant_dbus_dict_append_fixed_array(dict,
							"wep_key0",
							DBUS_TYPE_BYTE,
							&key, size / 2);
			g_free(key);
		} else if (size == 5 || size == 13) {
			unsigned char *key = g_try_malloc(13);
			int i;

			if (key == NULL)
				size = 0;

			for (i = 0; i < size; i++)
				key[i] = (unsigned char) ssid->passphrase[i];

			supplicant_dbus_dict_append_fixed_array(dict,
								"wep_key0",
								DBUS_TYPE_BYTE,
								&key, size);
			g_free(key);
		} else
			supplicant_dbus_dict_append_basic(dict,
							"wep_key0",
							DBUS_TYPE_STRING,
							&ssid->passphrase);

		supplicant_dbus_dict_append_basic(dict, "wep_tx_keyidx",
					DBUS_TYPE_STRING, &key_index);
	}
}
