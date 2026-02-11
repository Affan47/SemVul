__vpn_ipconfig_create(int index, int family)
{
	struct vpn_ipconfig *ipconfig;

	if (family == AF_INET6)
		return create_ipv6config(index);

	DBG("index %d", index);

	ipconfig = g_try_new0(struct vpn_ipconfig, 1);
	if (ipconfig == NULL)
		return NULL;

	ipconfig->refcount = 1;

	ipconfig->index = index;
	ipconfig->enabled = FALSE;
	ipconfig->family = family;

	ipconfig->address = connman_ipaddress_alloc(AF_INET);
	if (ipconfig->address == NULL) {
		g_free(ipconfig);
		return NULL;
	}

	ipconfig->system = connman_ipaddress_alloc(AF_INET);

	DBG("ipconfig %p", ipconfig);

	return ipconfig;
}
