vpn_provider_set_ipaddress(struct vpn_provider *provider,
					struct connman_ipaddress *ipaddress)
{
	struct vpn_ipconfig *ipconfig = NULL;

	switch (ipaddress->family) {
	case AF_INET:
		ipconfig = provider->ipconfig_ipv4;
		break;
	case AF_INET6:
		ipconfig = provider->ipconfig_ipv6;
		break;
	default:
		break;
	}

	DBG("provider %p ipconfig %p family %d", provider, ipconfig,
							ipaddress->family);

	if (ipconfig == NULL)
		return -EINVAL;

	provider->family = ipaddress->family;

	__vpn_ipconfig_set_local(ipconfig, ipaddress->local);
	__vpn_ipconfig_set_peer(ipconfig, ipaddress->peer);
	__vpn_ipconfig_set_broadcast(ipconfig, ipaddress->broadcast);
	__vpn_ipconfig_set_gateway(ipconfig, ipaddress->gateway);
	__vpn_ipconfig_set_prefixlen(ipconfig, ipaddress->prefixlen);

	return 0;
}
