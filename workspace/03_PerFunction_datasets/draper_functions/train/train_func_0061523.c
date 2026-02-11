nhrp_packet_xmit_timeout_cb(struct ev_timer *w, int revents)
{
	struct nhrp_packet *packet =
		container_of(w, struct nhrp_packet, timeout);

	list_del(&packet->request_list_entry);

	if (packet->dst_peer != NULL &&
	    ++packet->retry < PACKET_RETRIES) {
		nhrp_packet_marshall_and_send(packet);

		list_add(&packet->request_list_entry, &pending_requests);
	} else {
		ev_timer_stop(&packet->timeout);
		if (packet->dst_peer == NULL)
			nhrp_error("nhrp_packet_xmit_timeout: no destination peer!");
		if (packet->handler != NULL)
			packet->handler(packet->handler_ctx, NULL);
		nhrp_packet_dequeue(packet);
	}
}
