add_nameserver_route(int family, int index, char *nameserver,
				const char *gw)
{
	switch (family) {
	case AF_INET:
		if (connman_inet_compare_subnet(index, nameserver) == TRUE)
			break;

		if (connman_inet_add_host_route(index, nameserver, gw) < 0)

			connman_inet_add_host_route(index, nameserver, NULL);
		break;

	case AF_INET6:
		if (connman_inet_add_ipv6_host_route(index, nameserver,
								gw) < 0)
			connman_inet_add_ipv6_host_route(index, nameserver,
							NULL);
		break;
	}
}
