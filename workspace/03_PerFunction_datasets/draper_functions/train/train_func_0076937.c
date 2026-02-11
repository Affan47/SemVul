update_ip6_routing (NMPolicy *policy, gboolean force_update)
{
	NMPolicyPrivate *priv = NM_POLICY_GET_PRIVATE (policy);
	NMDevice *best = NULL, *parent;
	NMConnection *connection = NULL;
	NMVPNConnection *vpn = NULL;
	NMActiveConnection *best_ac = NULL;
	NMIP6Config *ip6_config = NULL, *parent_ip6;
	const char *ip_iface = NULL;
	int ip_ifindex = -1;
	guint32 parent_mss;
	guint32 i;
	const struct in6_addr *gw_addr;


	ip6_config = get_best_ip6_config (policy, FALSE, &ip_iface, &ip_ifindex, &best_ac, &best, &vpn);
	if (!ip6_config) {
		gboolean changed;

		changed = (priv->default_device6 != NULL);
		priv->default_device6 = NULL;
		if (changed)
			g_object_notify (G_OBJECT (policy), NM_POLICY_DEFAULT_IP6_DEVICE);

		return;
	}
	g_assert ((best || vpn) && best_ac);

	if (!force_update && best && (best == priv->default_device6))
		return;


	gw_addr = &in6addr_any;


	for (i = 0; i < nm_ip6_config_get_num_addresses (ip6_config); i++) {
		NMIP6Address *addr;

		addr = nm_ip6_config_get_address (ip6_config, i);
		if (nm_ip6_address_get_gateway (addr)) {
			gw_addr = nm_ip6_address_get_gateway (addr);
			break;
		}
	}


	if (   IN6_IS_ADDR_UNSPECIFIED (gw_addr)
	    && nm_ip6_config_get_gateway (ip6_config))
		gw_addr = nm_ip6_config_get_gateway (ip6_config);

	if (vpn) {
		parent = nm_vpn_connection_get_parent_device (vpn);
		parent_ip6 = nm_device_get_ip6_config (parent);
		parent_mss = parent_ip6 ? nm_ip6_config_get_mss (parent_ip6) : 0;

		nm_system_replace_default_ip6_route_vpn (ip_ifindex,
		                                         gw_addr,
		                                         nm_vpn_connection_get_ip6_internal_gateway (vpn),
		                                         nm_ip6_config_get_mss (ip6_config),
		                                         nm_device_get_ip_ifindex (parent),
		                                         parent_mss);
	} else {
		if (gw_addr)
			nm_system_replace_default_ip6_route (ip_ifindex, gw_addr);
		else
			nm_log_dbg (LOGD_IP6, "missing default IPv6 gateway");
	}

	update_default_ac (policy, best_ac, nm_active_connection_set_default6);
	priv->default_device6 = best;

	connection = nm_active_connection_get_connection (best_ac);
	nm_log_info (LOGD_CORE, "Policy set '%s' (%s) as default for IPv6 routing and DNS.",
	             nm_connection_get_id (connection), ip_iface);
	g_object_notify (G_OBJECT (policy), NM_POLICY_DEFAULT_IP6_DEVICE);
}
