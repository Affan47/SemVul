event_callback(struct net_connection* con, int events, void *arg)
{
	ADC_TRACE;
	struct ADC_client* client = (struct ADC_client*) net_con_get_ptr(con);

	switch (client->state)
	{
		case ps_conn:
			if (events == NET_EVENT_TIMEOUT)
			{
				client->callback(client, ADC_CLIENT_DISCONNECTED, 0);
				return;
			}
			break;

#ifdef SSL_SUPPORT
		case ps_conn_ssl:
			if (events == NET_EVENT_TIMEOUT)
			{
				client->callback(client, ADC_CLIENT_DISCONNECTED, 0);
				return;
			}

			if (events == NET_EVENT_ERROR)
			{
				ADC_client_on_disconnected(client);
				client->callback(client, ADC_CLIENT_DISCONNECTED, 0);
				return;
			}
			else
			{
				ADC_client_on_connected_ssl(client);
			}
			break;
#endif

		default:
			if (events & NET_EVENT_READ)
			{
				if (ADC_client_recv(client) == -1)
				{
					ADC_client_on_disconnected(client);
				}
			}

			if (events & NET_EVENT_WRITE)
			{
				ADC_client_send_queue(client);
			}
	}
}
