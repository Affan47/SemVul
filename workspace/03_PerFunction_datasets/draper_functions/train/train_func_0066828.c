flush_buffer(int fd, const char *buf, unsigned long size)
{
	while (size > 0) {
		long ret = write_in_full(fd, buf, size);
		if (ret < 0) {

			if (errno == EPIPE)
				break;
			die_errno("merge-recursive");
		} else if (!ret) {
			die("merge-recursive: disk full?");
		}
		size -= ret;
		buf += ret;
	}
}
