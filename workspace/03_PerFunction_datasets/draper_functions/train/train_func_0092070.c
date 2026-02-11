find_dline(struct sockaddr *addr, int aftype)
{
	struct ConfItem *aconf;
#ifdef RB_IPV6
	struct sockaddr_in addr2;
#endif

	aconf = find_conf_by_address(NULL, NULL, NULL, addr, CONF_EXEMPTDLINE | 1, aftype, NULL, NULL);
	if(aconf)
		return aconf;
	aconf = find_conf_by_address(NULL, NULL, NULL, addr, CONF_DLINE | 1, aftype, NULL, NULL);
	if(aconf)
		return aconf;
#ifdef RB_IPV6
	if(addr->sa_family == AF_INET6 &&
			ipv4_from_ipv6((const struct sockaddr_in6 *)(const void *)addr, &addr2))
	{
		aconf = find_conf_by_address(NULL, NULL, NULL, (struct sockaddr *)&addr2, CONF_DLINE | 1, AF_INET, NULL, NULL);
		if(aconf)
			return aconf;
	}
#endif
	return NULL;
}
