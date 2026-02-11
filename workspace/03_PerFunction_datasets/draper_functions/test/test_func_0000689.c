write_prefix(const char *buffer, size_t bytes, bool *prefixed)
{
	size_t i, j;
	const char *ec = ecolor(ECOLOR_HILITE);
	const char *ec_normal = ecolor(ECOLOR_NORMAL);
	ssize_t ret = 0;
	int fd = fileno(stdout), lock_fd = -1;


	lock_fd = open(PREFIX_LOCK, O_WRONLY | O_CREAT, 0664);

	if (lock_fd != -1) {
		while (flock(lock_fd, LOCK_EX) != 0) {
			if (errno != EINTR) {
				ewarnv("flock() failed: %s", strerror(errno));
				break;
			}
		}
	}
	else
		ewarnv("Couldn't open the prefix lock, please make sure you have enough permissions");

	for (i = 0; i < bytes; i++) {

		if (buffer[i] == '\033' && !*prefixed) {
			for (j = i + 1; j < bytes; j++) {
				if (buffer[j] == 'A')
					*prefixed = true;
				if (isalpha((unsigned int)buffer[j]))
					break;
			}
		}

		if (!*prefixed) {
			ret += write(fd, ec, strlen(ec));
			ret += write(fd, prefix, strlen(prefix));
			ret += write(fd, ec_normal, strlen(ec_normal));
			ret += write(fd, "|", 1);
			*prefixed = true;
		}

		if (buffer[i] == '\n')
			*prefixed = false;
		ret += write(fd, buffer + i, 1);
	}


	close(lock_fd);

	return ret;
}
