create_gsm_connect_properties (NMConnection *connection)
{
	NMSettingGsm *setting;
	NMSettingPPP *s_ppp;
	MMSimpleConnectProperties *properties;
	const gchar *str;

	setting = nm_connection_get_setting_gsm (connection);
	properties = mm_simple_connect_properties_new ();


	str = nm_setting_gsm_get_number (setting);
	if (str)
		mm_simple_connect_properties_set_number (properties, str);

	str = nm_setting_gsm_get_apn (setting);
	if (str)
		mm_simple_connect_properties_set_apn (properties, str);

	str = nm_setting_gsm_get_network_id (setting);
	if (str)
		mm_simple_connect_properties_set_operator_id (properties, str);

	str = nm_setting_gsm_get_pin (setting);
	if (str)
		mm_simple_connect_properties_set_pin (properties, str);

	str = nm_setting_gsm_get_username (setting);
	if (str)
		mm_simple_connect_properties_set_user (properties, str);

	str = nm_setting_gsm_get_password (setting);
	if (str)
		mm_simple_connect_properties_set_password (properties, str);


	if (nm_setting_gsm_get_home_only (setting))
		mm_simple_connect_properties_set_allow_roaming (properties, FALSE);


	s_ppp = nm_connection_get_setting_ppp (connection);
	if (s_ppp) {
		MMBearerAllowedAuth allowed_auth = MM_BEARER_ALLOWED_AUTH_UNKNOWN;

		if (nm_setting_ppp_get_noauth (s_ppp))
			allowed_auth = MM_BEARER_ALLOWED_AUTH_NONE;
		if (!nm_setting_ppp_get_refuse_pap (s_ppp))
			allowed_auth |= MM_BEARER_ALLOWED_AUTH_PAP;
		if (!nm_setting_ppp_get_refuse_chap (s_ppp))
			allowed_auth |= MM_BEARER_ALLOWED_AUTH_CHAP;
		if (!nm_setting_ppp_get_refuse_mschap (s_ppp))
			allowed_auth |= MM_BEARER_ALLOWED_AUTH_MSCHAP;
		if (!nm_setting_ppp_get_refuse_mschapv2 (s_ppp))
			allowed_auth |= MM_BEARER_ALLOWED_AUTH_MSCHAPV2;
		if (!nm_setting_ppp_get_refuse_eap (s_ppp))
			allowed_auth |= MM_BEARER_ALLOWED_AUTH_EAP;

		mm_simple_connect_properties_set_allowed_auth (properties, allowed_auth);
	}

	return properties;
}
