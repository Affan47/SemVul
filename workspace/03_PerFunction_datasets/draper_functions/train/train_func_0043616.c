dcc_str2ip(const char *str, IPADDR *ip)
{
	guint32 addr;

	if (strchr(str, ':') == NULL) {

                addr = strtoul(str, NULL, 10);
		ip->family = AF_INET;
		addr = (guint32) ntohl(addr);
		memcpy(&ip->ip, &addr, sizeof(addr));
	} else {

		net_host2ip(str, ip);
	}
}
