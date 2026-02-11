nm_system_add_ip4_vpn_gateway_route (NMDevice *parent_device, guint32 vpn_gw)
{
	NMIP4Config *parent_config;
	guint32 parent_gw = 0, parent_prefix = 0, i;
	NMIP4Address *tmp;
	struct rtnl_route *route = NULL;

	g_return_val_if_fail (NM_IS_DEVICE (parent_device), NULL);
	g_return_val_if_fail (vpn_gw != 0, NULL);


	parent_config = nm_device_get_ip4_config (parent_device);
	g_return_val_if_fail (parent_config != NULL, NULL);

	for (i = 0; i < nm_ip4_config_get_num_addresses (parent_config); i++) {
		tmp = nm_ip4_config_get_address (parent_config, i);
		if (nm_ip4_address_get_gateway (tmp)) {
			parent_gw = nm_ip4_address_get_gateway (tmp);
			parent_prefix = nm_ip4_address_get_prefix (tmp);
			break;
		}
	}

	if (!parent_gw)
		return NULL;


	if (ip4_dest_in_same_subnet (parent_config, vpn_gw, parent_prefix)) {
		route = nm_system_device_set_ip4_route (nm_device_get_ip_ifindex (parent_device),
		                                        vpn_gw, 32, 0, 0, nm_ip4_config_get_mss (parent_config));
	} else {
		route = nm_system_device_set_ip4_route (nm_device_get_ip_ifindex (parent_device),
		                                        vpn_gw, 32, parent_gw, 0, nm_ip4_config_get_mss (parent_config));
	}

	return route;
}
