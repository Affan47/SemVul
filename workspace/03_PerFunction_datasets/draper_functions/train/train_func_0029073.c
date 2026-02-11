print_ipv6addr_array(struct dhcpv6_option *opt, void (*print)(const char *fmt, ...))
{
	char str[INET6_ADDRSTRLEN];
	int i;
	int f = 0;
	struct in6_addr *addr = (struct in6_addr *)opt->hdr->data;

	for (i = ntohs(opt->hdr->len) / sizeof(*addr); i; i--, addr++) {
		inet_ntop(AF_INET6, addr, str, sizeof(str));
		print("%c%s", f ? ',' : ' ', str);
		f = 1;
	}
}
