sockaddr_init(sockaddr_t *addr, int af)
{

	memset(addr, 0, sizeof(sockaddr_t));


	switch(af) {
	case AF_INET:
		addr->len = sizeof(struct sockaddr_in);
		addr->prefix = IPV4_PREFIXLEN;
		break;
#ifndef DISABLE_IPV6
	case AF_INET6:
		addr->len = sizeof(struct sockaddr_in6);
		addr->prefix = IPV6_PREFIXLEN;
		break;
#endif
	default:
		return -1;
	}

	return 0;
}
