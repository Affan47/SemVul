interface_add_network_params(DBusMessageIter *iter, void *user_data)
{
	DBusMessageIter dict;
	struct interface_connect_data *data = user_data;
	GSupplicantSSID *ssid = data->ssid;

	supplicant_dbus_dict_open(iter, &dict);

	if (ssid->scan_ssid)
		supplicant_dbus_dict_append_basic(&dict, "scan_ssid",
					 DBUS_TYPE_UINT32, &ssid->scan_ssid);

	if (ssid->freq)
		supplicant_dbus_dict_append_basic(&dict, "frequency",
					 DBUS_TYPE_UINT32, &ssid->freq);

	if (ssid->bgscan != NULL)
		supplicant_dbus_dict_append_basic(&dict, "bgscan",
					DBUS_TYPE_STRING, &ssid->bgscan);

	add_network_mode(&dict, ssid);

	add_network_security(&dict, ssid);

	supplicant_dbus_dict_append_fixed_array(&dict, "ssid",
					DBUS_TYPE_BYTE, &ssid->ssid,
						ssid->ssid_len);

	supplicant_dbus_dict_close(iter, &dict);
}
