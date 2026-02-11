lttng_live_send(int fd, const void *buf, size_t len)
{
	ssize_t ret;

	do {
		ret = send(fd, buf, len, MSG_NOSIGNAL);
	} while (ret < 0 && errno == EINTR);
	return ret;
}
