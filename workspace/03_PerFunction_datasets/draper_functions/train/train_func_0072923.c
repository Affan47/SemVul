tcp_write(rdpTcp* tcp, uint8* data, int length)
{
	int status;
	int sent = 0;

	while (sent < length)
	{
		status = send(tcp->sockfd, data, (length - sent), MSG_NOSIGNAL);

		if (status < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				continue;

			perror("send");
			return -1;
		}
		else
		{
			sent += status;
			data += status;
		}
	}

	return sent;
}
