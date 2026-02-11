copy_tcp_connection(tcp_connection_t *p_dest_connection,
		const tcp_connection_t *p_source_connection)
{
	if (!p_dest_connection || !p_source_connection) {
		return -1;
	}

	p_dest_connection->local_addr = p_source_connection->local_addr;
	p_dest_connection->local_port = p_source_connection->local_port;
	p_dest_connection->remote_addr = p_source_connection->remote_addr;
	p_dest_connection->remote_port = p_source_connection->remote_port;
	p_dest_connection->age = p_source_connection->age;

	return 0;
}
