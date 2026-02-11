network_create_unix_udp_client(struct network_client *client)
{
	int sockfd;

	sockfd = unix_create_service(SOCK_DGRAM, NULL);
	if (sockfd < 0)
	{
		pr_red_info("unix_create_service");
		return sockfd;
	}

	client->sockfd = sockfd;

	return 0;
}
