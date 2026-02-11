net_read(int sockfd, long timeout, char *buf, size_t count)
{
	char *b;
	ssize_t bytes;

	for (b = buf; count; count -= bytes, b += bytes)
	{
		if (read_timeout(sockfd, timeout, 0) == -1)
			return -1;

		if ((bytes = read(sockfd, b, count)) == -1)
			return -1;

		if (bytes == 0)
			break;
	}

	return b - buf;
}
