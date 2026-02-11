net_destroy_packet(net_packet_t *packet)
{
	if (packet) {
		if (packet->ip) {
			free(packet->ip);
		}
		if (packet->udp) {
			free(packet->udp);
		}
		if (packet->dns) {
			free(packet->dns);
		}
		if (packet->rr_q) {
			free(packet->rr_q);
		}
		if (packet->rr_a) {
			free(packet->rr_a);
		}
		free(packet);
	}
}
