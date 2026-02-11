_get_block(char *buffer, size_t buf_size)
{
	static int fd = 0;
	ssize_t buf_used = 0, rc;

	if (!fd) {
		fd = open(params.src_fname, O_RDONLY);
		if (!fd) {
			error("Can't open `%s`: %s",
			      params.src_fname, strerror(errno));
			exit(1);
		}
	}

	while (buf_size) {
		rc = read(fd, buffer, buf_size);
		if (rc == -1) {
			if ((errno == EINTR) || (errno == EAGAIN))
				continue;
			error("Can't read `%s`: %s",
			      params.src_fname, strerror(errno));
			exit(1);
		} else if (rc == 0) {
			debug("end of file reached");
			break;
		}

		buffer   += rc;
		buf_size -= rc;
		buf_used += rc;
	}
	return buf_used;
}
