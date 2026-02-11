yield_recv()
{
	uint32_t ticks;
	uint32_t cur_ticks;
	struct inet_address sender;
	struct packet_header *h;
	int ret;

	h = (struct packet_header *)recv_buf;

	ticks = misc.get_time();
	cur_ticks = ticks;

	while (cur_ticks < ticks + 50) {
		int player_id;
		struct mp_msg *msg;
		char *buf_copy;

		h->size = MP_UDP_MAX_PACKET_SIZE;

		ret = network->recv(game_sock, h, &sender);
		if (ret <= 0)
			return;

		player_id = get_player_id(&sender);
		if (!player_id && status == MP_STATUS_PREGAME) {
			if (host_flag)
				udp_accept_connections(h, &sender);
			continue;
		}

		if (h->size <= 0 || h->size >= MP_UDP_MAX_PACKET_SIZE)
			continue;


		switch (h->type) {
		case PACKET_STREAM:
		case PACKET_NONSEQ:
			msg = new struct mp_msg;
			buf_copy = new char[h->size];

			msg->player_id = player_id;
			memcpy(&msg->header, h, sizeof(struct packet_header));
			msg->size = h->size;
			msg->data = buf_copy;
			memcpy(buf_copy, (char *)h+sizeof(struct packet_header), h->size);
			recv_queue.push(msg);
			break;
		case PACKET_SYSTEM:
			break;
		}
	}
}
