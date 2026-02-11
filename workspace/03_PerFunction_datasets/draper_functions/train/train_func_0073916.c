ipv6_network_addr (const struct in6_addr *addr,
                   const struct in6_addr *mask,
                   struct in6_addr *res)
{
	gint i;

	for (i = 0; i < 16; ++i) {
		res->s6_addr[i] = addr->s6_addr[i] & mask->s6_addr[i];
	}
}
