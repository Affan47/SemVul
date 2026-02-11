ud_connect(const char *name)
{
	int fd;
	int r;
	struct sockaddr_un addr;

	fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (fd < 0) {
		return fd;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	sprintf(addr.sun_path, "%s", name);

	r = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
	if (r < 0) {
		close(fd);
		return r;
	}

	return fd;
}
