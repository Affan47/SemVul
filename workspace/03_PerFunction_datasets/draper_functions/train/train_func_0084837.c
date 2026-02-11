sendto_select(int sockfd, int retry, const void *buff, size_t len, const struct sockaddr_in *remote_addr)
{
	while (retry--)
	{
		ssize_t sendlen;

		sendlen = inet_sendto(sockfd, buff, len, remote_addr);
		if (sendlen < 0)
		{
			print_error("send data failed");
			return sendlen;
		}

		if (file_poll_input(sockfd, NETWORK_TIMEOUT_VALUE))
		{
			return sendlen;
		}

		println("timeout retry = %d", retry);
	}

	return -ETIMEDOUT;
}
