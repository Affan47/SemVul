create_connect_properties (NMConnection *connection)
{
	NMSettingGsm *setting;
	NMSettingPPP *s_ppp;
	GHashTable *properties;
	const char *str;

	setting = nm_connection_get_setting_gsm (connection);
	properties = value_hash_create ();

	str = nm_setting_gsm_get_number (setting);
	if (str)
		value_hash_add_str (properties, "number", str);

	str = nm_setting_gsm_get_apn (setting);
	if (str)
		value_hash_add_str (properties, "apn", str);

	str = nm_setting_gsm_get_network_id (setting);
	if (str)
		value_hash_add_str (properties, "network_id", str);

	str = nm_setting_gsm_get_pin (setting);
	if (str)
		value_hash_add_str (properties, "pin", str);

	str = nm_setting_gsm_get_username (setting);
	if (str)
		value_hash_add_str (properties, "username", str);

	str = nm_setting_gsm_get_password (setting);
	if (str)
		value_hash_add_str (properties, "password", str);


	switch (nm_setting_gsm_get_network_type (setting)) {
	case NM_SETTING_GSM_NETWORK_TYPE_UMTS_HSPA:
		value_hash_add_uint (properties, "network_mode", MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_3G_ONLY);
		value_hash_add_uint (properties, "allowed_mode", MM_MODEM_GSM_ALLOWED_MODE_3G_ONLY);
		break;
	case NM_SETTING_GSM_NETWORK_TYPE_GPRS_EDGE:
		value_hash_add_uint (properties, "network_mode", MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_2G_ONLY);
		value_hash_add_uint (properties, "allowed_mode", MM_MODEM_GSM_ALLOWED_MODE_2G_ONLY);
		break;
	case NM_SETTING_GSM_NETWORK_TYPE_PREFER_UMTS_HSPA:
		value_hash_add_uint (properties, "network_mode", MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_3G_PREFERRED);
		value_hash_add_uint (properties, "allowed_mode", MM_MODEM_GSM_ALLOWED_MODE_3G_PREFERRED);
		break;
	case NM_SETTING_GSM_NETWORK_TYPE_PREFER_GPRS_EDGE:
		value_hash_add_uint (properties, "network_mode", MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_2G_PREFERRED);
		value_hash_add_uint (properties, "allowed_mode", MM_MODEM_GSM_ALLOWED_MODE_2G_PREFERRED);
		break;
	case NM_SETTING_GSM_NETWORK_TYPE_PREFER_4G:

		value_hash_add_uint (properties, "allowed_mode", MM_MODEM_GSM_ALLOWED_MODE_4G_PREFERRED);
		break;
	case NM_SETTING_GSM_NETWORK_TYPE_4G:

		value_hash_add_uint (properties, "allowed_mode", MM_MODEM_GSM_ALLOWED_MODE_4G_ONLY);
		break;
	default:
		value_hash_add_uint (properties, "network_mode", MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_ANY);
		value_hash_add_uint (properties, "allowed_mode", MM_MODEM_GSM_ALLOWED_MODE_ANY);
		break;
	}


	if (nm_setting_gsm_get_home_only (setting))
		value_hash_add_bool (properties, "home_only", TRUE);


	s_ppp = nm_connection_get_setting_ppp (connection);
	if (s_ppp) {
		guint32 auth = MM_MODEM_GSM_ALLOWED_AUTH_UNKNOWN;

		if (nm_setting_ppp_get_noauth (s_ppp))
			auth |= MM_MODEM_GSM_ALLOWED_AUTH_NONE;
		if (!nm_setting_ppp_get_refuse_pap (s_ppp))
			auth |= MM_MODEM_GSM_ALLOWED_AUTH_PAP;
		if (!nm_setting_ppp_get_refuse_chap (s_ppp))
			auth |= MM_MODEM_GSM_ALLOWED_AUTH_CHAP;
		if (!nm_setting_ppp_get_refuse_mschap (s_ppp))
			auth |= MM_MODEM_GSM_ALLOWED_AUTH_MSCHAP;
		if (!nm_setting_ppp_get_refuse_mschapv2 (s_ppp))
			auth |= MM_MODEM_GSM_ALLOWED_AUTH_MSCHAPV2;
		if (!nm_setting_ppp_get_refuse_eap (s_ppp))
			auth |= MM_MODEM_GSM_ALLOWED_AUTH_EAP;

		if (auth != MM_MODEM_GSM_ALLOWED_AUTH_UNKNOWN)
			value_hash_add_uint (properties, "allowed_auth", auth);
	}

	return properties;
}
