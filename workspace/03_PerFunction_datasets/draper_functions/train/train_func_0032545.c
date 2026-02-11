create_tcp_port_monitor(in_port_t port_range_begin,
		in_port_t port_range_end, tcp_port_monitor_args_t *p_creation_args)
{
	tcp_port_monitor_t *p_monitor;


	p_monitor = (tcp_port_monitor_t *) calloc(1, sizeof(tcp_port_monitor_t));
	if (!p_monitor) {
		return NULL;
	}

	p_monitor->max_port_monitor_connections =
		p_creation_args->max_port_monitor_connections;


	g_sprintf(p_monitor->key, ":%04X :%04X", port_range_begin, port_range_end);


	if ((p_monitor->hash = g_hash_table_new(tcp_connection_hash, tcp_connection_equal)) == NULL) {


		destroy_tcp_port_monitor(p_monitor, NULL);
		return NULL;
	}


	if ((p_monitor->p_peek = (tcp_connection_t **)
			calloc(p_monitor->max_port_monitor_connections,
			sizeof(tcp_connection_t *))) == NULL) {


		destroy_tcp_port_monitor(p_monitor, NULL);
		return NULL;
	}

	p_monitor->port_range_begin = port_range_begin;
	p_monitor->port_range_end = port_range_end;

	p_monitor->connection_list.p_head = NULL;
	p_monitor->connection_list.p_tail = NULL;

	return p_monitor;
}
