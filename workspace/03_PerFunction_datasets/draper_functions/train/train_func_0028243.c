dump_in6_addr_port(uint16_t *addr, uint16_t port, char *buf, int *len)
{
	sprintf(buf, "%x:%x:%x:%x:%x:%x:%x:%x-%d",
                ntohs(addr[0]),
                ntohs(addr[1]),
                ntohs(addr[2]),
                ntohs(addr[3]),
                ntohs(addr[4]),
                ntohs(addr[5]),
                ntohs(addr[6]),
                ntohs(addr[7]),
                ntohs(port));

	if (len)
		*len = strlen(buf);

	return buf;
}
