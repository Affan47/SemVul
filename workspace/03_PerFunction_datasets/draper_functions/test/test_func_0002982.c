make_test_wsec_setting (const char *detail)
{
	NMSettingWirelessSecurity *s_wsec;

	s_wsec = (NMSettingWirelessSecurity *) nm_setting_wireless_security_new ();
	ASSERT (s_wsec != NULL, detail, "error creating setting");

	g_object_set (s_wsec,
	              NM_SETTING_WIRELESS_SECURITY_KEY_MGMT, "wpa-psk",
	              NM_SETTING_WIRELESS_SECURITY_LEAP_USERNAME, "foobarbaz",
	              NM_SETTING_WIRELESS_SECURITY_PSK, "random psk",
	              NM_SETTING_WIRELESS_SECURITY_WEP_KEY0, "aaaaaaaaaa",
	              NULL);

	return s_wsec;
}
