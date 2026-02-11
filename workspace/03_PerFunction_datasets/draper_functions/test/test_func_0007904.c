create_empty_packet(const size_t max_size)
{

	knot_packet_t *packet = knot_packet_new();
	if (packet == NULL) {
		DBG_NULL;
		return NULL;
	}


	knot_packet_set_max_size(packet, max_size);


	knot_query_init(packet);


	knot_packet_set_random_id(packet);

	return packet;
}
