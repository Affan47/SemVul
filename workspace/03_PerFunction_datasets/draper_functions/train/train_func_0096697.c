ietadm_request_listen(void)
{
	int fd, err;
	struct sockaddr_un addr;

	fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (fd < 0)
		return fd;

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_LOCAL;
	memcpy((char *) &addr.sun_path + 1, IETADM_NAMESPACE, strlen(IETADM_NAMESPACE));

	if ((err = bind(fd, (struct sockaddr *) &addr, sizeof(addr))) < 0)
		return err;

	if ((err = listen(fd, 32)) < 0)
		return err;

	return fd;
}
