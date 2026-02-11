connman_inet_add_network_route(int index, const char *host,
					const char *gateway,
					const char *netmask)
{
	struct ifreq ifr;
	struct rtentry rt;
	struct sockaddr_in addr;
	int sk, err = 0;

	DBG("index %d host %s gateway %s netmask %s", index,
		host, gateway, netmask);

	sk = socket(PF_INET, SOCK_DGRAM | SOCK_CLOEXEC, 0);
	if (sk < 0) {
		err = -errno;
		goto out;
	}

	memset(&ifr, 0, sizeof(ifr));
	ifr.ifr_ifindex = index;

	if (ioctl(sk, SIOCGIFNAME, &ifr) < 0) {
		err = -errno;
		close(sk);
		goto out;
	}

	DBG("ifname %s", ifr.ifr_name);

	memset(&rt, 0, sizeof(rt));
	rt.rt_flags = RTF_UP;
	if (gateway != NULL)
		rt.rt_flags |= RTF_GATEWAY;
	if (netmask == NULL)
		rt.rt_flags |= RTF_HOST;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(host);
	memcpy(&rt.rt_dst, &addr, sizeof(rt.rt_dst));

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	if (gateway != NULL)
		addr.sin_addr.s_addr = inet_addr(gateway);
	else
		addr.sin_addr.s_addr = INADDR_ANY;
	memcpy(&rt.rt_gateway, &addr, sizeof(rt.rt_gateway));

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	if (netmask != NULL)
		addr.sin_addr.s_addr = inet_addr(netmask);
	else
		addr.sin_addr.s_addr = INADDR_ANY;
	memcpy(&rt.rt_genmask, &addr, sizeof(rt.rt_genmask));

	rt.rt_dev = ifr.ifr_name;

	if (ioctl(sk, SIOCADDRT, &rt) < 0 && errno != EEXIST)
		err = -errno;

	close(sk);

out:
	if (err < 0)
		connman_error("Adding host route failed (%s)",
							strerror(-err));

	return err;
}
