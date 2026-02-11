network_client_timed_recv(struct network_client *client, void *buff, size_t size, int timeout)
{
	if (file_poll_input(client->sockfd, timeout))
	{
		return client->recv(client, buff, size);
	}

	return -ETIMEDOUT;
}
