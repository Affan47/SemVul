handle_net_write(struct hub_user* user)
{
	int ret = 0;
	while (ioq_send_get_bytes(user->send_queue))
	{
		ret = ioq_send_send(user->send_queue, user->connection);
		if (ret <= 0)
			break;
	}

	if (ret < 0)
		return quit_socket_error;

	if (ioq_send_get_bytes(user->send_queue))
	{
		user_net_io_want_write(user);
	}
	else
	{
		user_net_io_want_read(user);
	}
	return 0;
}
