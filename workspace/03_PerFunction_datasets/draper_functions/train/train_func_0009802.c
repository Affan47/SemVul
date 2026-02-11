rinoo_socket_class_tcp_create(t_sched *sched)
{
	t_socket *socket;

	socket = calloc(1, sizeof(*socket));
	if (unlikely(socket == NULL)) {
		return NULL;
	}
	socket->node.sched = sched;
	return socket;
}
