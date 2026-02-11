is_connection_always_ask (NMConnection *connection)
{
	NMSettingConnection *s_con;
	const char *ctype;
	NMSetting *setting;


	s_con = nm_connection_get_setting_connection (connection);
	g_assert (s_con);
	ctype = nm_setting_connection_get_connection_type (s_con);

	setting = nm_connection_get_setting_by_name (connection, ctype);
	g_return_val_if_fail (setting != NULL, FALSE);

	if (has_always_ask (setting))
		return TRUE;


	if (NM_IS_SETTING_WIRELESS (setting)) {
		setting = nm_connection_get_setting (connection, NM_TYPE_SETTING_WIRELESS_SECURITY);
		if (setting && has_always_ask (setting))
			return TRUE;
		setting = nm_connection_get_setting (connection, NM_TYPE_SETTING_802_1X);
		if (setting && has_always_ask (setting))
			return TRUE;
	} else if (NM_IS_SETTING_WIRED (setting)) {
		setting = nm_connection_get_setting (connection, NM_TYPE_SETTING_PPPOE);
		if (setting && has_always_ask (setting))
			return TRUE;
		setting = nm_connection_get_setting (connection, NM_TYPE_SETTING_802_1X);
		if (setting && has_always_ask (setting))
			return TRUE;
	}

	return FALSE;
}
