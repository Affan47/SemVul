ip6_requires_slaves (NMConnection *connection)
{
	NMSettingIP6Config *s_ip6;
	const char *method = NM_SETTING_IP6_CONFIG_METHOD_AUTO;

	s_ip6 = nm_connection_get_setting_ip6_config (connection);
	if (s_ip6)
		method = nm_setting_ip6_config_get_method (s_ip6);


	return    g_strcmp0 (method, NM_SETTING_IP6_CONFIG_METHOD_AUTO) == 0
	       || g_strcmp0 (method, NM_SETTING_IP6_CONFIG_METHOD_DHCP) == 0
	       || g_strcmp0 (method, NM_SETTING_IP6_CONFIG_METHOD_LINK_LOCAL) == 0;
}
