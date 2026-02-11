mpd_socket_connect(const char *host, unsigned port, const struct timeval *tv0,
		   struct mpd_error_info *error)
{
	struct timeval tv = *tv0;
	struct resolver *resolver;
	const struct resolver_address *address;
	int fd, ret;

	resolver = resolver_new(host, port);
	if (resolver == NULL) {
		mpd_error_code(error, MPD_ERROR_RESOLVER);
		mpd_error_message(error, "Failed to resolve host name");
		return -1;
	}

	assert(!mpd_error_is_defined(error));

	while ((address = resolver_next(resolver)) != NULL) {
		fd = socket_cloexec_nonblock(address->family, SOCK_STREAM,
					     address->protocol);
		if (fd < 0) {
			mpd_error_clear(error);
			mpd_error_errno(error);
			continue;
		}

		ret = connect(fd, address->addr, address->addrlen);
		if (ret == 0) {
			resolver_free(resolver);
			mpd_error_clear(error);
			return fd;
		}

		if (!ignore_errno(mpd_socket_errno())) {
			mpd_error_clear(error);
			mpd_error_errno(error);

			mpd_socket_close(fd);
			continue;
		}

		ret = mpd_socket_wait_connected(fd, &tv);
		if (ret > 0) {
			resolver_free(resolver);
			mpd_error_clear(error);
			return fd;
		}

		if (ret == 0) {
			mpd_error_clear(error);
			mpd_error_code(error, MPD_ERROR_TIMEOUT);
			mpd_error_message(error, "Timeout while connecting");
		} else if (ret < 0) {
			mpd_error_clear(error);
			mpd_error_system_message(error, -ret);
		}

		mpd_socket_close(fd);
	}

	resolver_free(resolver);
	return -1;
}
