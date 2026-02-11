inc_global_cidr_count(struct Client *client_p)
{
	struct rb_sockaddr_storage ip;
	struct sockaddr *addr;
	int bitlen;

	if(!MyClient(client_p))
	{
		if(EmptyString(client_p->sockhost) || !strcmp(client_p->sockhost, "0"))
			return -1;
		if(!rb_inet_pton_sock(client_p->sockhost, (struct sockaddr *)&ip))
			return -1;
		addr = (struct sockaddr *)&ip;
	}
	else
		addr = (struct sockaddr *)&client_p->localClient->ip;
#ifdef RB_IPV6
	if(GET_SS_FAMILY(addr) == AF_INET6)
	{
		bitlen = ConfigFileEntry.global_cidr_ipv6_bitlen;
	}
	else
#endif
		bitlen = ConfigFileEntry.global_cidr_ipv4_bitlen;

	return inc_global_ip(addr, bitlen);
}
