gnapplet_get_addrlen(const unsigned char *addr)
{
	if (!addr[0]) return 0;

	return (addr[0] + 1) / 2 + 1;
}
