network_client_recv_sync(struct network_client *client, void *buff, size_t size)
{
	ssize_t length;
	struct cavan_sync_package *package;
	struct network_client_sync_data *data = network_client_get_data(client);
	struct pollfd pfd =
	{
		.fd = client->sockfd,
		.events = POLLIN,
	};

	package = alloca(size + sizeof(struct cavan_sync_package));
	if (package == NULL)
	{
		pr_error_info("alloca");
		return -ENOMEM;
	}

	pthread_mutex_lock(&data->lock);

	data->recv_pending++;

	while (1)
	{
		int ret;
		ssize_t rdlen, wrlen;

		pthread_mutex_unlock(&data->lock);
		ret = poll(&pfd, 1, CAVAN_NET_UDP_ACTIVE_TIME);
		pthread_mutex_lock(&data->lock);
		if (ret < 1)
		{
			pr_red_info("file_poll_input");
			length = -ETIMEDOUT;
			goto out_clean_pending;
		}

		if (poll(&pfd, 1, 0) < 1)
		{
			continue;
		}

		rdlen = data->recv(client, package, size + sizeof(struct cavan_sync_package));
		if (rdlen < (ssize_t) sizeof(struct cavan_sync_package))
		{
			length = -EFAULT;
			goto out_clean_pending;
		}

		length = package->length;

		if (package->type == CAVAN_SYNC_TYPE_DATA)
		{
			if ((size_t) rdlen == length + sizeof(struct cavan_sync_package))
			{
				package->length = 0;
				package->type = CAVAN_SYNC_TYPE_ACK;

				wrlen = data->send(client, package, sizeof(struct cavan_sync_package));
				if (wrlen != sizeof(struct cavan_sync_package))
				{
					pr_red_info("data->send");
					length = -EFAULT;
					goto out_clean_pending;
				}

				if (package->index == data->recv_index)
				{
					break;
				}
			}
		}
		else if (package->type == CAVAN_SYNC_TYPE_ACK)
		{
			if (package->index == data->send_index)
			{
				data->send_index++;
			}
		}

#if CAVAN_NETWORK_DEBUG
		pd_red_info("index not match, recv_index = %d, index = %d, type = %d, length = %d",
			data->recv_index, package->index, package->type, package->length);
#endif
	}

	data->recv_index++;
	mem_copy(buff, package->data, length);

out_clean_pending:
	data->recv_pending--;
	pthread_mutex_unlock(&data->lock);
	return length;
}
