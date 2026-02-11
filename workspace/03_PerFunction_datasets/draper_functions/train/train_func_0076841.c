free_free_queue(nic_t *nic)
{
	packet_t *pkt, *pkt_next;

	pthread_mutex_lock(&nic->free_packet_queue_mutex);
	pkt = nic->free_packet_queue;
	while (pkt) {
		pkt_next = pkt->next;
		free_packet(pkt);
		pkt = pkt_next;
	}
	nic->free_packet_queue = NULL;
	pthread_mutex_unlock(&nic->free_packet_queue_mutex);
}
