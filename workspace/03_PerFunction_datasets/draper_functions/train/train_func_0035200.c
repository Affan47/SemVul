client_initialize(size_t max_clients)
{
	clients = (client_t **) calloc(max_clients, sizeof(client_t *));
	if(clients == NULL)
	{
		perror("client_initialize():");
		return -1;
	}

	client_limit = max_clients;

	return 0;
}
