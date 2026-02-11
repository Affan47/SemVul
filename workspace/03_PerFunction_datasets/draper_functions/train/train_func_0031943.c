nm_vpn_connection_apply_config (NMVPNConnection *connection)
{
	NMVPNConnectionPrivate *priv = NM_VPN_CONNECTION_GET_PRIVATE (connection);

	nm_system_iface_set_up (priv->ip_ifindex, TRUE, NULL);

	if (priv->ip4_config) {
		if (!nm_system_apply_ip4_config (priv->ip_ifindex, priv->ip4_config,
		                                 0, NM_IP4_COMPARE_FLAG_ALL))
			return FALSE;
	}

	if (priv->ip6_config) {
		if (!nm_system_apply_ip6_config (priv->ip_ifindex, priv->ip6_config,
		                                 0, NM_IP6_COMPARE_FLAG_ALL))

			return FALSE;
	}


	if (priv->ip4_external_gw) {
		priv->gw_route = nm_system_add_ip4_vpn_gateway_route (priv->parent_dev,
		                                                      priv->ip4_external_gw);
	} else if (priv->ip6_external_gw) {
		priv->gw_route = nm_system_add_ip6_vpn_gateway_route (priv->parent_dev,
		                                                      priv->ip6_external_gw);
	} else {
		priv->gw_route = NULL;
	}

	nm_log_info (LOGD_VPN, "VPN connection '%s' (IP Config Get) complete.",
	             nm_connection_get_id (priv->connection));
	nm_vpn_connection_set_vpn_state (connection,
	                                 NM_VPN_CONNECTION_STATE_ACTIVATED,
	                                 NM_VPN_CONNECTION_STATE_REASON_NONE);
	return TRUE;
}
