isns_addr_get_port(const struct sockaddr *addr)
{
	const struct sockaddr_in *sin;
	const struct sockaddr_in6 *six;

	switch (addr->sa_family) {
	case AF_INET:
		sin = (const struct sockaddr_in *) addr;
		return ntohs(sin->sin_port);

	case AF_INET6:
		six = (const struct sockaddr_in6 *) addr;
		return ntohs(six->sin6_port);
	}
	return 0;
}
