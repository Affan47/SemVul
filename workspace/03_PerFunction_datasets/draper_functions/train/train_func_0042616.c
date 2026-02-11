create_inet_socket()
{
	int fd, on = 1;
	struct sockaddr_in sin;
	int sockflags;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		logerror("syslog: Unknown protocol, suspending inet service.");
		return fd;
	}

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = LogPort;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, \
		       (char *) &on, sizeof(on)) < 0 ) {
		logerror("setsockopt(REUSEADDR), suspending inet");
		close(fd);
		return -1;
	}


	if ((sockflags = fcntl(fd, F_GETFL)) != -1) {
		sockflags |= O_NONBLOCK;


		sockflags = fcntl(fd, F_SETFL, sockflags);
	}
	if (sockflags == -1) {
		logerror("fcntl(O_NONBLOCK), suspending inet");
		close(fd);
		return -1;
	}
	if (bind(fd, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
		logerror("bind, suspending inet");
		close(fd);
		return -1;
	}
	return fd;
}
