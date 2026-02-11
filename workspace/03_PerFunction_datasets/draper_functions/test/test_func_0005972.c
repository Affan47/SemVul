dyn_dns_init(DYN_DNS_CLIENT *p_self)
{
	int i = 0;

	if (p_self == NULL)
	{
		return RC_INVALID_POINTER;
	}

	if (p_self->initialized == TRUE)
	{
		return RC_OK;
	}

	p_self->abort_on_network_errors = FALSE;
	p_self->force_addr_update = FALSE;

	do
	{
		DYNDNS_INFO_TYPE *info = &p_self->info[i];

		if (strlen(info->proxy_server_name.name) > 0)
		{
			http_client_set_port(&p_self->http_to_ip_server[i], info->proxy_server_name.port);
			http_client_set_remote_name(&p_self->http_to_ip_server[i], info->proxy_server_name.name);

			http_client_set_port(&p_self->http_to_dyndns[i], info->proxy_server_name.port);
			http_client_set_remote_name(&p_self->http_to_dyndns[i], info->proxy_server_name.name);
		}
		else
		{
			http_client_set_port(&p_self->http_to_ip_server[i], info->ip_server_name.port);
			http_client_set_remote_name(&p_self->http_to_ip_server[i], info->ip_server_name.name);

			http_client_set_port(&p_self->http_to_dyndns[i], info->dyndns_server_name.port);
			http_client_set_remote_name(&p_self->http_to_dyndns[i], info->dyndns_server_name.name);
		}

		http_client_set_bind_iface(&p_self->http_to_dyndns[i], p_self->bind_interface);
		http_client_set_bind_iface(&p_self->http_to_ip_server[i], p_self->bind_interface);
	}
	while (++i < p_self->info_count);

	p_self->cmd = NO_CMD;
	if (p_self->cmd_check_period == 0)
	{
		p_self->cmd_check_period = DYNDNS_DEFAULT_CMD_CHECK_PERIOD;
	}


	p_self->time_since_last_update = cached_time_since_last_update;
	p_self->num_iterations = cached_num_iterations;

	p_self->initialized = TRUE;

	return RC_OK;
}
