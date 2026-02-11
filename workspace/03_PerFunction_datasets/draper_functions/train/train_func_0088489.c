write_or_die(int fd, const void *buf, size_t count)
{
	if (write_in_full(fd, buf, count) != count)
		die("write_or_die: %s", strerror(errno));
}
