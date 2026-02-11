tls_socket_close(rad_listen_t *listener)
{
	listen_socket_t *sock = listener->data;

	listener->status = RAD_LISTEN_STATUS_REMOVE_FD;
	listener->tls = NULL;

	if (sock->parent) {


		if (sock->parent->num_connections > 0) {
			sock->parent->num_connections--;
		}
		if (sock->client->num_connections > 0) {
			sock->client->num_connections--;
		}
	}


	DEBUG("Client has closed connection");
	event_new_fd(listener);


}
