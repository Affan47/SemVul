del_routes(struct gateway_data *data,
			enum connman_ipconfig_type type)
{
	int status4 = 0, status6 = 0;
	int do_ipv4 = FALSE, do_ipv6 = FALSE;

	if (type == CONNMAN_IPCONFIG_TYPE_IPV4)
		do_ipv4 = TRUE;
	else if (type == CONNMAN_IPCONFIG_TYPE_IPV6)
		do_ipv6 = TRUE;
	else
		do_ipv4 = do_ipv6 = TRUE;

	if (do_ipv4 == TRUE && data->ipv4_gateway != NULL) {
		if (data->ipv4_gateway->vpn == TRUE) {
			status4 = connman_inet_clear_gateway_address(
						data->index,
						data->ipv4_gateway->vpn_ip);

		} else if (g_strcmp0(data->ipv4_gateway->gateway,
							"0.0.0.0") == 0) {
			status4 = connman_inet_clear_gateway_interface(
								data->index);
		} else {
			connman_inet_del_host_route(data->index,
						data->ipv4_gateway->gateway);
			status4 = connman_inet_clear_gateway_address(
						data->index,
						data->ipv4_gateway->gateway);
		}
	}

	if (do_ipv6 == TRUE && data->ipv6_gateway != NULL) {
		if (data->ipv6_gateway->vpn == TRUE) {
			status6 = connman_inet_clear_ipv6_gateway_address(
						data->index,
						data->ipv6_gateway->vpn_ip);

		} else if (g_strcmp0(data->ipv6_gateway->gateway, "::") == 0) {
			status6 = connman_inet_clear_ipv6_gateway_interface(
								data->index);
		} else {
			connman_inet_del_ipv6_host_route(data->index,
						data->ipv6_gateway->gateway);
			status6 = connman_inet_clear_ipv6_gateway_address(
						data->index,
						data->ipv6_gateway->gateway);
		}
	}

	return (status4 < 0 ? status4 : status6);
}
