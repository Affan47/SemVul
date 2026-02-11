open_tun(const char *tun_device)
{
	int i;
	int tun_fd;
	struct ifreq ifreq;
	char *tunnel = "/dev/net/tun";

	if ((tun_fd = open(tunnel, O_RDWR)) < 0) {
		warn("open_tun: %s: %s", tunnel, strerror(errno));
		return -1;
	}

	memset(&ifreq, 0, sizeof(ifreq));

	ifreq.ifr_flags = IFF_TUN;

	if (tun_device != NULL) {
		strncpy(ifreq.ifr_name, tun_device, IFNAMSIZ);
		ifreq.ifr_name[IFNAMSIZ-1] = '\0';
		strncpy(if_name, tun_device, sizeof(if_name));
		if_name[sizeof(if_name)-1] = '\0';

		if (ioctl(tun_fd, TUNSETIFF, (void *) &ifreq) != -1) {
			fprintf(stderr, "Opened %s\n", ifreq.ifr_name);
			return tun_fd;
		}

		if (errno != EBUSY) {
			warn("open_tun: ioctl[TUNSETIFF]: %s", strerror(errno));
			return -1;
		}
	} else {
		for (i = 0; i < TUN_MAX_TRY; i++) {
			snprintf(ifreq.ifr_name, IFNAMSIZ, "dns%d", i);

			if (ioctl(tun_fd, TUNSETIFF, (void *) &ifreq) != -1) {
				fprintf(stderr, "Opened %s\n", ifreq.ifr_name);
				snprintf(if_name, sizeof(if_name), "dns%d", i);
				return tun_fd;
			}

			if (errno != EBUSY) {
				warn("open_tun: ioctl[TUNSETIFF]: %s", strerror(errno));
				return -1;
			}
		}

		warn("open_tun: Couldn't set interface name");
	}
	warn("error when opening tun");
	return -1;
}
