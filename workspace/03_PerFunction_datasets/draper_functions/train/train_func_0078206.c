inet_tcp_send_file1(int sockfd, int fd)
{
	ssize_t readlen, sendlen;
	char buff[1024];

	while (1)
	{
		readlen = read(fd, buff, sizeof(buff));
		if (readlen < 0)
		{
			print_error("read");
			return readlen;
		}

		if (readlen == 0)
		{
			break;
		}

		sendlen = inet_send(sockfd, buff, readlen);
		if (sendlen < 0)
		{
			print_error("inet_send");
			return sendlen;
		}
	}

	return 0;
}
