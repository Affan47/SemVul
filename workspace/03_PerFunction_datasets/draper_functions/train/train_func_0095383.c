adb_read_status(int sockfd, char *buff, size_t size)
{
	int ret;
	ssize_t recvlen;

	recvlen = inet_recv(sockfd, buff, size > 8 ? 8 : size - 1);
	if (recvlen < 0)
	{
		text_copy(buff, "protocol fault (no status)");
		return recvlen;
	}

	buff[recvlen] = 0;
	ret = text_lhcmp("OKAY", buff) ? -EFAULT : 0;

	if (recvlen == 8)
	{
		size_t length;

		length = text2value_unsigned(buff + 4, NULL, 16);
		if (length >= size)
		{
			length = size - 1;
		}

		recvlen = inet_recv(sockfd, buff, length);
		if (recvlen < 0)
		{
			return recvlen;
		}

		buff[recvlen] = 0;
	}

	return ret;
}
