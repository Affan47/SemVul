get_default_type_for_security (NMSettingWirelessSecurity *sec)
{
	const char *key_mgmt, *auth_alg;

	g_return_val_if_fail (sec != NULL, NMU_SEC_NONE);

	key_mgmt = nm_setting_wireless_security_get_key_mgmt (sec);
	auth_alg = nm_setting_wireless_security_get_auth_alg (sec);


	if (!strcmp (key_mgmt, "none"))
		return NMU_SEC_STATIC_WEP;

	if (!strcmp (key_mgmt, "ieee8021x")) {
		if (auth_alg && !strcmp (auth_alg, "leap"))
			return NMU_SEC_LEAP;
		return NMU_SEC_DYNAMIC_WEP;
	}

	if (!strcmp (key_mgmt, "wpa-psk")) {
		if (find_proto (sec, "rsn"))
			return NMU_SEC_WPA2_PSK;
		else if (find_proto (sec, "wpa"))
			return NMU_SEC_WPA_PSK;
		else
			return NMU_SEC_WPA_PSK;
	}

	if (!strcmp (key_mgmt, "wpa-eap")) {
		if (find_proto (sec, "rsn"))
			return NMU_SEC_WPA2_ENTERPRISE;
		else if (find_proto (sec, "wpa"))
			return NMU_SEC_WPA_ENTERPRISE;
		else
			return NMU_SEC_WPA_ENTERPRISE;
	}

	return NMU_SEC_INVALID;
}
