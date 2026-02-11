wext_interface(char *ifname)
{
	struct iwreq wrq;
	int fd, err;

	fd = socket(PF_INET, SOCK_DGRAM | SOCK_CLOEXEC, 0);
	if (fd < 0)
		return FALSE;

	memset(&wrq, 0, sizeof(wrq));
	strncpy(wrq.ifr_name, ifname, IFNAMSIZ);

	err = ioctl(fd, SIOCGIWNAME, &wrq);

	close(fd);

	if (err < 0)
		return FALSE;

	return TRUE;
}
