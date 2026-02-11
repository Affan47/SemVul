net_ip2host(IPADDR *ip, char *host)
{
#ifdef HAVE_IPV6
	if (!inet_ntop(ip->family, &ip->ip, host, MAX_IP_LEN))
		return -1;
#else
	unsigned long ip4;

	if (ip->family != AF_INET) {
		strcpy(host, "0.0.0.0");
	} else {
		ip4 = ntohl(ip->ip.s_addr);
		g_snprintf(host, MAX_IP_LEN, "%lu.%lu.%lu.%lu",
			   (ip4 & 0xff000000UL) >> 24,
			   (ip4 & 0x00ff0000) >> 16,
			   (ip4 & 0x0000ff00) >> 8,
			   (ip4 & 0x000000ff));
	}
#endif
	return 0;
}
