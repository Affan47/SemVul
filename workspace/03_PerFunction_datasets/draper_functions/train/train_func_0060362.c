network_client_udp_common_open(struct network_client *client, struct sockaddr *addr, int flags)
{
	int ret;

	if (addr && (flags & CAVAN_NET_FLAG_TALK))
	{
		ret = network_client_udp_talk(client, addr);
		if (ret < 0)
		{
			pr_red_info("network_client_udp_talk");
			return ret;
		}

		ret = connect(client->sockfd, addr, client->addrlen);
		if (ret < 0)
		{
			pr_error_info("connect");
			return ret;
		}
	}

	client->send = network_client_tcp_send;
	client->recv = network_client_tcp_recv;
	client->close = network_client_tcp_close;

	if (flags & CAVAN_NET_FLAG_SYNC)
	{
		ret = network_client_set_sync(client);
		if (ret < 0)
		{
			pr_red_info("network_client_set_sync");
			return ret;
		}
	}

	return 0;
}
