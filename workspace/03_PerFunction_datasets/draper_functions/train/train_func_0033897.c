get_dest_addr(int family, int index, char *buf, int len)
{
	struct ifreq ifr;
	void *addr;
	int sk;

	sk = socket(family, SOCK_DGRAM | SOCK_CLOEXEC, 0);
	if (sk < 0)
		return -errno;

	memset(&ifr, 0, sizeof(ifr));
	ifr.ifr_ifindex = index;

	if (ioctl(sk, SIOCGIFNAME, &ifr) < 0) {
		DBG("SIOCGIFNAME (%d/%s)", errno, strerror(errno));
		close(sk);
		return -errno;
	}

	if (ioctl(sk, SIOCGIFFLAGS, &ifr) < 0) {
		DBG("SIOCGIFFLAGS (%d/%s)", errno, strerror(errno));
		close(sk);
		return -errno;
	}

	if ((ifr.ifr_flags & IFF_POINTOPOINT) == 0) {
		close(sk);
		errno = EINVAL;
		return -errno;
	}

	DBG("index %d %s", index, ifr.ifr_name);

	if (ioctl(sk, SIOCGIFDSTADDR, &ifr) < 0) {
		connman_error("Get destination address failed (%s)",
							strerror(errno));
		close(sk);
		return -errno;
	}

	close(sk);

	switch (family) {
	case AF_INET:
		addr = &((struct sockaddr_in *)&ifr.ifr_dstaddr)->sin_addr;
		break;
	case AF_INET6:
		addr = &((struct sockaddr_in6 *)&ifr.ifr_dstaddr)->sin6_addr;
		break;
	default:
		errno = EINVAL;
		return -errno;
	}

	if (inet_ntop(family, addr, buf, len) == NULL) {
		DBG("error %d/%s", errno, strerror(errno));
		return -errno;
	}

	return 0;
}
