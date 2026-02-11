socket_suspend(struct pcmcia_socket *skt)
{
	if (skt->state & SOCKET_SUSPEND)
		return -EBUSY;

	mutex_lock(&skt->ops_mutex);
	skt->suspended_state = skt->state;

	skt->socket = dead_socket;
	skt->ops->set_socket(skt, &skt->socket);
	if (skt->ops->suspend)
		skt->ops->suspend(skt);
	skt->state |= SOCKET_SUSPEND;
	mutex_unlock(&skt->ops_mutex);
	return 0;
}
