tunet_connect_keepalive_server()
{
	if(keepalive_socket == 0 && strlen(keepalive_server) != 0)
		keepalive_socket = os_socket_tcp_connect(keepalive_server, keepalive_server_port, TRUE);

	return OK;
}
