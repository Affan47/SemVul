vdi_dns_comp_addrinfo6(const struct backend *bp,
		       const struct sockaddr_storage *addr,
		       const socklen_t len)
{
	const uint8_t *u, *p;
	const struct sockaddr_in6 *bps = (const void *)bp->ipv6;
	const struct sockaddr_in6 *bpd = (const void *)addr;

	if (bp->ipv6len != len || len <= 0)
		return (0);

	u = bpd->sin6_addr.s6_addr;
	p = bps->sin6_addr.s6_addr;

	return (!memcmp(u, p, 16));
}
