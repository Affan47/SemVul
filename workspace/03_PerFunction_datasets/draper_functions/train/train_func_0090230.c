resolve_addr6(const char *name, struct in6_addr *inp)
{
	if (IN6_IS_ADDR_UNSPECIFIED(inp->s6_addr32))
	{
		puts("any");
		return;
	}

	if (IN6_IS_ADDR_LOOPBACK(inp->s6_addr32))
	{
		puts("loopback");
		return;
	}

	print_hostbyaddr(name, (const char *) inp, sizeof(*inp), AF_INET6);
}
