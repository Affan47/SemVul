net_connect(const char *addr, int port, IPADDR *my_ip)
{
	IPADDR ip4, ip6, *ip;

	g_return_val_if_fail(addr != NULL, NULL);

	if (net_gethostbyname(addr, &ip4, &ip6) == -1)
		return NULL;

	if (my_ip == NULL) {

		ip = ip4.family != 0 ? &ip4 : &ip6;
	} else if (IPADDR_IS_V6(my_ip)) {

		if (ip6.family != 0)
			ip = &ip6;
		else {
			my_ip = NULL;
                        ip = &ip4;
		}
	} else {

		if (ip4.family != 0)
			ip = &ip4;
		else {
			my_ip = NULL;
                        ip = &ip6;
		}
	}

	return net_connect_ip(ip, port, my_ip);
}
