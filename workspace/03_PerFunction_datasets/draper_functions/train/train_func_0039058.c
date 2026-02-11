irmo_server_shutdown(IrmoServer *server)
{
	irmo_return_if_fail(server != NULL);


        server_disconnect_all_clients(server);


	while (irmo_hash_table_num_entries(server->clients)) {
		irmo_server_run(server);
		irmo_net_socket_block(server->socket, 100);
	}

	irmo_server_internal_shutdown(server);
}
