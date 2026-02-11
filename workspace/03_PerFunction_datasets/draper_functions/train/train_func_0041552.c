verify_leap (NMSettingWirelessSecurity *s_wsec,
             NMSetting8021x *s_8021x,
             gboolean adhoc,
             GError **error)
{
	const char *key_mgmt, *auth_alg, *leap_username;

	key_mgmt = nm_setting_wireless_security_get_key_mgmt (s_wsec);
	auth_alg = nm_setting_wireless_security_get_auth_alg (s_wsec);
	leap_username = nm_setting_wireless_security_get_leap_username (s_wsec);


	if (auth_alg) {
		if (!strcmp (auth_alg, "leap")) {

			if (!leap_username) {
				g_set_error_literal (error,
				                     NM_SETTING_WIRELESS_SECURITY_ERROR,
				                     NM_SETTING_WIRELESS_SECURITY_ERROR_LEAP_REQUIRES_USERNAME,
				                     "LEAP requires a LEAP username");
				return FALSE;
			}
		} else if (leap_username) {

			g_set_error_literal (error,
			                     NM_SETTING_WIRELESS_SECURITY_ERROR,
			                     NM_SETTING_WIRELESS_SECURITY_ERROR_INVALID_PROPERTY,
			                     "LEAP requires 'leap' authentication");
			return FALSE;
		}
	}

	if (leap_username) {
		if (key_mgmt && strcmp (key_mgmt, "ieee8021x")) {

			g_set_error_literal (error,
			                     NM_SETTING_WIRELESS_SECURITY_ERROR,
			                     NM_SETTING_WIRELESS_SECURITY_ERROR_LEAP_REQUIRES_802_1X,
			                     "LEAP requires IEEE 802.1x key management");
			return FALSE;
		}
	}


	if (leap_username) {
		if (auth_alg)
			g_assert (strcmp (auth_alg, "leap") == 0);
		if (key_mgmt)
			g_assert (strcmp (key_mgmt, "ieee8021x") == 0);

		if (adhoc) {
			g_set_error_literal (error,
			                     NM_SETTING_WIRELESS_SECURITY_ERROR,
			                     NM_SETTING_WIRELESS_SECURITY_ERROR_INVALID_PROPERTY,
			                     "LEAP incompatible with Ad-Hoc mode");
			return FALSE;
		}

		if (!verify_no_wep (s_wsec, "LEAP", error))
			return FALSE;

		if (s_8021x) {
			g_set_error_literal (error,
			                     NM_SETTING_WIRELESS_SECURITY_ERROR,
			                     NM_SETTING_WIRELESS_SECURITY_ERROR_LEAP_REQUIRES_USERNAME,
			                     "LEAP incompatible with 802.1x setting");
			return FALSE;
		}
	}

	return TRUE;
}
