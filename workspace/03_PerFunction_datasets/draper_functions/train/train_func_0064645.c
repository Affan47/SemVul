get_ipv6(glibtop *server, glibtop_netload *buf,
		     const char *interface)
{
	struct ifaddrs *ifa0, *ifr6;

	if(getifaddrs (&ifa0) != 0)
	{
		glibtop_warn_r(server, "getifaddrs failed : %s", g_strerror(errno));
		return;
	}

	for (ifr6 = ifa0; ifr6; ifr6 = ifr6->ifa_next) {
		if (strcmp (ifr6->ifa_name, interface) == 0
		    && ifr6->ifa_addr != NULL
		    && ifr6->ifa_addr->sa_family == AF_INET6)
			break;
	}

	if(!ifr6) goto free_ipv6;

	memcpy(buf->address6,
	       &((struct sockaddr_in6 *) ifr6->ifa_addr)->sin6_addr,
	       16);

	memcpy(buf->prefix6,
	       &((struct sockaddr_in6 *) ifr6->ifa_netmask)->sin6_addr,
	       16);


	if (IN6_IS_ADDR_LINKLOCAL (buf->address6))
		buf->scope6 = GLIBTOP_IF_IN6_SCOPE_LINK;

	else if (IN6_IS_ADDR_SITELOCAL (buf->address6))
		buf->scope6 = GLIBTOP_IF_IN6_SCOPE_SITE;

	else if (IN6_IS_ADDR_GLOBAL (buf->address6)
		 || IN6_IS_ADDR_MC_ORGLOCAL (buf->address6)
		 || IN6_IS_ADDR_V4COMPAT (buf->address6)
		 || IN6_IS_ADDR_MULTICAST (buf->address6)
		 || IN6_IS_ADDR_UNSPECIFIED (buf->address6)
		)
		buf->scope6 = GLIBTOP_IF_IN6_SCOPE_GLOBAL;

	else if (IN6_IS_ADDR_LOOPBACK (buf->address6))
		buf->scope6 = GLIBTOP_IF_IN6_SCOPE_HOST;

	else
		buf->scope6 = GLIBTOP_IF_IN6_SCOPE_UNKNOWN;

	buf->flags |= _glibtop_sysdeps_netload_6;

 free_ipv6:
	freeifaddrs(ifa0);
}
