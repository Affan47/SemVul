isns_portal_from_sockaddr(isns_portal_info_t *portal,
		const struct sockaddr_storage *addr)
{
	struct sockaddr_in6 *six;
	struct sockaddr_in *sin;

	memset(portal, 0, sizeof(*portal));


	six = &portal->addr;
	switch (addr->ss_family) {
	case AF_INET6:
		memcpy(six, addr, sizeof(*six));
		break;

	case AF_INET:
		sin = (struct sockaddr_in *) addr;
		six->sin6_family = AF_INET6;
		six->sin6_addr.s6_addr32[3] = sin->sin_addr.s_addr;
		six->sin6_port = sin->sin_port;
		break;

	default:
		return 0;
	}

	return 1;
}
