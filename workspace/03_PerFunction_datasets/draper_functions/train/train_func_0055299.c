ftp_server_receive_file1(struct network_client *client, const struct network_url *url, int fd)
{
	int ret;

	ret = ftp_create_data_link(client, url);
	if (ret < 0)
	{
		pr_red_info("ftp_create_data_link");
		return ret;
	}

	ret = network_client_recv_file(client, fd, 0);

	network_client_close(client);

	return ret;
}
