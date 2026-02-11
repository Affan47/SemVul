nm_vpn_connection_config_get (DBusGProxy *proxy,
                              GHashTable *config_hash,
                              gpointer user_data)
{
	NMVPNConnection *connection = NM_VPN_CONNECTION (user_data);
	NMVPNConnectionPrivate *priv = NM_VPN_CONNECTION_GET_PRIVATE (connection);
	GValue *val;

	nm_log_info (LOGD_VPN, "VPN connection '%s' (IP Config Get) reply received.",
	             nm_connection_get_id (priv->connection));

	if (!process_generic_config (connection, config_hash))
		return;


	val = g_hash_table_lookup (config_hash, NM_VPN_PLUGIN_CONFIG_HAS_IP4);
	priv->has_ip4 = val ? g_value_get_boolean (val) : FALSE;
	g_clear_object (&priv->ip4_config);

	val = g_hash_table_lookup (config_hash, NM_VPN_PLUGIN_CONFIG_HAS_IP6);
	priv->has_ip6 = val ? g_value_get_boolean (val) : FALSE;
	g_clear_object (&priv->ip6_config);
}
