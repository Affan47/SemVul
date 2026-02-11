gfire_p2p_natcheck_dnsquery(GSList *p_hosts, gpointer p_data, const char *p_error)
{
	gfire_p2p_natcheck *nat = (gfire_p2p_natcheck*)p_data;
	if(!nat)
		return;

	if(!p_hosts)
	{
		purple_debug_error("gfire", "P2P: NAT Check: Hostname lookup failed for \"%s\"\n", purple_dnsquery_get_host(nat->dnsdata));
		nat->state = GF_NATCHECK_DONE;
		nat->type = 0;
		if(nat->callback) nat->callback(0, 0, 0, nat->callback_data);
		return;
	}

	int server = -1;
	switch(nat->state)
	{
	case GF_NATCHECK_DNS1:
		server = 0; break;
	case GF_NATCHECK_DNS2:
		server = 1; break;
	case GF_NATCHECK_DNS3:
		server = 2; break;
	default:
		break;
	}

	GSList *hosts = p_hosts;
	while(hosts)
	{
		size_t len = GPOINTER_TO_INT(hosts->data);
		hosts = g_slist_next(hosts);

		struct sockaddr *addr = (struct sockaddr*)hosts->data;
		if(addr->sa_family == AF_INET)
		{
			memset(&nat->nat_servers[server], 0, sizeof(struct sockaddr_in));
			memcpy(&nat->nat_servers[server], addr, len);
		}
		g_free(addr);

		hosts = g_slist_next(hosts);
	}
	g_slist_free(p_hosts);

	purple_debug_misc("gfire", "P2P: NAT Check: Server %d: %u.%u.%u.%u\n", server + 1,
					  (g_ntohl(nat->nat_servers[server].sin_addr.s_addr) & 0xff000000) >> 24,
					  (g_ntohl(nat->nat_servers[server].sin_addr.s_addr) & 0xff0000) >> 16,
					  (g_ntohl(nat->nat_servers[server].sin_addr.s_addr) & 0xff00) >> 8,
					  g_ntohl(nat->nat_servers[server].sin_addr.s_addr) & 0xff);

	nat->dnsdata = NULL;

	switch(nat->state)
	{
	case GF_NATCHECK_DNS1:
		nat->state = GF_NATCHECK_DNS2;
		nat->dnsdata = purple_dnsquery_a(XFIRE_NAT_SERVER2, XFIRE_NAT_PORT, gfire_p2p_natcheck_dnsquery, nat);
		break;
	case GF_NATCHECK_DNS2:
		nat->state = GF_NATCHECK_DNS3;
		nat->dnsdata = purple_dnsquery_a(XFIRE_NAT_SERVER3, XFIRE_NAT_PORT, gfire_p2p_natcheck_dnsquery, nat);
		break;
	case GF_NATCHECK_DNS3:
		gfire_p2p_natcheck_start_query(nat);
		break;
	default:
		break;
	}
}
