connect_to(resolve_info *ri, char **message)
{
	struct addrinfo *rp = ri -> alist[ri -> index];

	int fd = socket(rp -> ai_family, rp -> ai_socktype, rp -> ai_protocol);
	if (fd == -1)
	{
		asprintf(message, "could not create socket: %s (%d)", strerror(errno), errno);
		ri -> index = (ri -> index + 1) % ri -> alist_n;
		return -1;
	}

	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
	{
		asprintf(message, "fcnt(O_NONBLOCK) failed: %s (%d)", strerror(errno), errno);
		close(fd);
		ri -> index = (ri -> index + 1) % ri -> alist_n;
		return -1;
	}

	set_ka(fd);

	set_no_delay(fd);


	if (connect(fd, rp -> ai_addr, rp -> ai_addrlen) == 0)
		return fd;

	if (errno == EINPROGRESS)
	{

		return fd;
	}

	asprintf(message, "connect failed: %s (%d)", strerror(errno), errno);

	close(fd);

	ri -> index = (ri -> index + 1) % ri -> alist_n;

	return -1;
}
