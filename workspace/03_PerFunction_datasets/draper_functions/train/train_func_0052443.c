hash_ipv4(struct sockaddr *saddr, int bits)
{
	struct sockaddr_in *addr = (struct sockaddr_in *)(void *)saddr;

	if(bits != 0)
	{
		uint32_t av = ntohl(addr->sin_addr.s_addr) & ~((1 << (32 - bits)) - 1);
		return (av ^ (av >> 12) ^ (av >> 24)) & (ATABLE_SIZE - 1);
	}

	return 0;
}
