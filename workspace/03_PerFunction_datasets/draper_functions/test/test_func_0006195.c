xread(int fd, void *buf, size_t count)
{
	if (count) {
		ssize_t size = full_read(fd, buf, count);
		if ((size_t)size != count)
			bb_error_msg_and_die("short read");
	}
}
