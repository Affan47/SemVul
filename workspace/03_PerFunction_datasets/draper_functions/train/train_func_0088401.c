net_vsend(int sockfd, long timeout, const char *format, va_list args)
{
	char buf[MSG_SIZE + 1];
	ssize_t bytes;

	bytes = vsnprintf(buf, MSG_SIZE + 1, format, args);
	if (bytes == -1 || bytes > MSG_SIZE)
		return set_errno(ENOSPC);

	return net_write(sockfd, timeout, buf, bytes);
}
