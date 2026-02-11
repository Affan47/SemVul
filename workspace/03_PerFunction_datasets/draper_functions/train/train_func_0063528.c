connman_network_set_ipaddress(struct connman_network *network,
					struct connman_ipaddress *ipaddress)
{
	struct connman_service *service;
	struct connman_ipconfig *ipconfig = NULL;

	DBG("network %p", network);

	service = connman_service_lookup_from_network(network);
	if (service == NULL)
		return -EINVAL;

	ipconfig = __connman_service_get_ipconfig(service, ipaddress->family);
	if (ipconfig == NULL)
		return -EINVAL;

	__connman_ipconfig_set_local(ipconfig, ipaddress->local);
	__connman_ipconfig_set_peer(ipconfig, ipaddress->peer);
	__connman_ipconfig_set_broadcast(ipconfig, ipaddress->broadcast);
	__connman_ipconfig_set_prefixlen(ipconfig, ipaddress->prefixlen);
	__connman_ipconfig_set_gateway(ipconfig, ipaddress->gateway);

	return 0;
}
