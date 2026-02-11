client_add(client_t *client)
{
	int fd = client->connection_fd;
	if(clients[fd])
	{
		fprintf(stderr, "client_add(fd=%d): Error, el cliente ya existe\n", fd);
		return -1;
	}

	clients[fd] = client;

	return 0;
}
