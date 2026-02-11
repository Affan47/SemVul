dhcpv6_confirm(struct connman_dhcpv6 *dhcp)
{
	GDHCPClient *dhcp_client;
	GDHCPClientError error;
	struct connman_service *service;
	struct connman_ipconfig *ipconfig_ipv6;
	int index, ret;

	DBG("dhcp %p", dhcp);

	index = connman_network_get_index(dhcp->network);

	dhcp_client = g_dhcp_client_new(G_DHCP_IPV6, index, &error);
	if (error != G_DHCP_CLIENT_ERROR_NONE) {
		clear_timer(dhcp);
		return -EINVAL;
	}

	if (getenv("CONNMAN_DHCPV6_DEBUG"))
		g_dhcp_client_set_debug(dhcp_client, dhcpv6_debug, "DHCPv6");

	service = connman_service_lookup_from_network(dhcp->network);
	if (service == NULL) {
		clear_timer(dhcp);
		g_dhcp_client_unref(dhcp_client);
		return -EINVAL;
	}

	ret = set_duid(service, dhcp->network, dhcp_client, index);
	if (ret < 0) {
		clear_timer(dhcp);
		g_dhcp_client_unref(dhcp_client);
		return ret;
	}

	g_dhcp_client_set_request(dhcp_client, G_DHCPV6_CLIENTID);
	g_dhcp_client_set_request(dhcp_client, G_DHCPV6_RAPID_COMMIT);
	g_dhcp_client_set_request(dhcp_client, G_DHCPV6_DNS_SERVERS);
	g_dhcp_client_set_request(dhcp_client, G_DHCPV6_SNTP_SERVERS);

	g_dhcpv6_client_set_oro(dhcp_client, 2, G_DHCPV6_DNS_SERVERS,
				G_DHCPV6_SNTP_SERVERS);

	ipconfig_ipv6 = __connman_service_get_ip6config(service);
	dhcp->use_ta = __connman_ipconfig_ipv6_privacy_enabled(ipconfig_ipv6);

	g_dhcpv6_client_set_ia(dhcp_client, index,
			dhcp->use_ta == TRUE ? G_DHCPV6_IA_TA : G_DHCPV6_IA_NA,
			NULL, NULL, TRUE,
			__connman_ipconfig_get_dhcp_address(ipconfig_ipv6));

	clear_callbacks(dhcp_client);

	g_dhcp_client_register_event(dhcp_client,
				G_DHCP_CLIENT_EVENT_CONFIRM,
				confirm_cb, dhcp);

	dhcp->dhcp_client = dhcp_client;

	return g_dhcp_client_start(dhcp_client, NULL);
}
