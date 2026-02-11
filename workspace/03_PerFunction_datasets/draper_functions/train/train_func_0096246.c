rinoo_socket_class_ssl_create(t_sched *sched)
{
	t_ssl *ssl;

	ssl = calloc(1, sizeof(*ssl));
	if (unlikely(ssl == NULL)) {
		return NULL;
	}
	ssl->socket.node.sched = sched;
	return &ssl->socket;
}
