ux_socket_connect(const char *name)
{
	int fd;
	struct sockaddr_un addr;

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, name, sizeof(addr.sun_path));

	fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (fd == -1) {
		return -1;
	}

	if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		close(fd);
		return -1;
	}

	return fd;
}
