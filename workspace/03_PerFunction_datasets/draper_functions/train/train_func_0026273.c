nm_gconf_read_0_6_vpn_connection (GConfClient *client,
						    const char *dir)
{
	NMConnection *connection;
	NMSettingConnection *s_con;
	NMSettingVPN *s_vpn;
	NMSettingIP4Config *s_ip4 = NULL;
	char *path, *network, *id = NULL, *uuid = NULL, *service_name = NULL;
	GSList *str_routes = NULL, *vpn_data = NULL;

	path = g_path_get_dirname (dir);
	network = g_path_get_basename (dir);

	if (!get_mandatory_string_helper (client, path, "name", network, &id)) {
		g_free (path);
		g_free (network);
		return NULL;
	}
	if (!get_mandatory_string_helper (client, path, "service_name", network, &service_name)) {
		g_free (id);
		g_free (path);
		g_free (network);
		return NULL;
	}

	if (!nm_gconf_get_stringlist_helper (client, path, "routes", network, &str_routes))
		str_routes = NULL;
	if (!nm_gconf_get_stringlist_helper (client, path, "vpn_data", network, &vpn_data))
		vpn_data = NULL;

	s_con = (NMSettingConnection *)nm_setting_connection_new ();
	g_object_set (s_con,
				  NM_SETTING_CONNECTION_ID, id,
				  NM_SETTING_CONNECTION_TYPE, NM_SETTING_VPN_SETTING_NAME,
				  NULL);

	uuid = nm_utils_uuid_generate ();
	g_object_set (s_con, NM_SETTING_CONNECTION_UUID, uuid, NULL);

	s_vpn = (NMSettingVPN *)nm_setting_vpn_new ();
	g_object_set (s_vpn, NM_SETTING_VPN_SERVICE_TYPE, service_name, NULL);

	if (!strcmp (service_name, NM_VPNC_SERVICE))
		nm_gconf_0_6_vpnc_settings (s_vpn, vpn_data, uuid, id);
	else if (!strcmp (service_name, "org.freedesktop.NetworkManager.openvpn"))
		nm_gconf_0_6_openvpn_settings (s_vpn, vpn_data);
	else
		g_warning ("unmatched service name %s\n", service_name);

	nm_utils_slist_free (vpn_data, g_free);
	g_free (path);
	g_free (network);
	g_free (service_name);

	if (str_routes) {
		s_ip4 = NM_SETTING_IP4_CONFIG (nm_setting_ip4_config_new ());
		g_object_set (s_ip4, NM_SETTING_IP4_CONFIG_METHOD, NM_SETTING_IP4_CONFIG_METHOD_AUTO, NULL);
		add_routes (s_ip4, str_routes);
	}

	connection = nm_connection_new ();
	nm_connection_add_setting (connection, NM_SETTING (s_con));
	nm_connection_add_setting (connection, NM_SETTING (s_vpn));
	if (s_ip4)
		nm_connection_add_setting (connection, NM_SETTING (s_ip4));

	g_free (id);
	g_free (uuid);

	return connection;
}
