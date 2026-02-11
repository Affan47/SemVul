ipset_contains_host(const ipset_t *ips, const gnet_host_t *h, bool any)
{
	ipset_check(ips);
	g_assert(h != NULL);

	if G_UNLIKELY(NULL != ips->addrs) {
		host_addr_t ha = gnet_host_get_addr(h);
		return hset_contains(ips->addrs, &ha);
	} else {
		return any;
	}
}
