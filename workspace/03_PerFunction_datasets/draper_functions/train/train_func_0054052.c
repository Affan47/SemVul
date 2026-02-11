tnl_get_ioctl(const char *basedev, void *p)
{
	struct ifreq ifr;
	int fd;
	int err;

	strncpy(ifr.ifr_name, basedev, IFNAMSIZ);
	ifr.ifr_ifru.ifru_data = (void*)p;
	fd = socket(preferred_family, SOCK_DGRAM, 0);
	err = ioctl(fd, SIOCGETTUNNEL, &ifr);
	if (err)
		fprintf(stderr, "get tunnel \"%s\" failed: %s\n", basedev,
			strerror(errno));

	close(fd);
	return err;
}
