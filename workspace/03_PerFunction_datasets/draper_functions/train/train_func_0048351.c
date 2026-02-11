ifname2sockaddr(ifname, index, addr)
	const char *ifname;
	int index;
	struct sockaddr *addr;
{
	int i;
	struct ifaddrs ifa, *ifap = &ifa, *iface;

	if (getifaddrs(&ifap) != 0)
		return NULL;

	for (iface = ifap, i = 0; i <= index && iface != NULL;
	iface = iface->ifa_next)
		if (strcmp(iface->ifa_name, ifname) == 0
		&& iface->ifa_addr != NULL && iface->ifa_addr->sa_family == AF_INET) {
			if (i++ != index)
				continue;

			*addr = *iface->ifa_addr;
			freeifaddrs(ifap);
			return addr;
		}

	freeifaddrs(ifap);
	return NULL;
}
