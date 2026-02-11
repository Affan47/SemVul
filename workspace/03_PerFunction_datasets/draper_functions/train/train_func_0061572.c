gf_sk_ipv6_set_remote_address(GF_Socket *sock, const char *address, u16 PortNumber)
{
	struct addrinfo *res = gf_sk_get_ipv6_addr(address, PortNumber, AF_UNSPEC, 0, (sock->flags & GF_SOCK_IS_TCP) ? SOCK_STREAM : SOCK_DGRAM);
	if (!res) return 0;
    memcpy(&sock->dest_addr, res->ai_addr, res->ai_addrlen);
	sock->dest_addr_len = res->ai_addrlen;
	freeaddrinfo(res);
	return 1;
}
