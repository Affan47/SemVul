get_ll (struct ifaddrs *ifaddrs, struct ifaddrs **ifa, char *name)
{
	for (*ifa = ifaddrs; *ifa != NULL; *ifa = (*ifa)->ifa_next) {
		if ((*ifa)->ifa_addr == NULL)
			continue;

		if ((*ifa)->ifa_addr->sa_family != AF_PACKET)
			continue;

		if ((*ifa)->ifa_flags & IFF_LOOPBACK)
			continue;

		if (strcmp((*ifa)->ifa_name, name) == 0)
			return (struct sockaddr_ll *)(void *)(*ifa)->ifa_addr;
	}
	return NULL;
}
