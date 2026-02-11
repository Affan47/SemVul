network_client_unix_udp_open(struct network_client *client, const struct network_url *url, u16 port, int flags)
{
	int ret;
	struct sockaddr_un addr;

	ret = network_create_unix_udp_client(client);
	if (ret < 0)
	{
		pr_error_info("inet_socket");
		return ret;
	}

	unix_sockaddr_init(&addr, url->pathname);
	client->addrlen = sizeof(struct sockaddr_un);

	ret = network_client_udp_common_open(client, (struct sockaddr *) &addr, flags);
	if (ret < 0)
	{
		pr_red_info("network_client_udp_common_open");
		goto out_close_sockfd;
	}

	return 0;

out_close_sockfd:
	close(client->sockfd);
	return ret;
}
