ps_packet_write(ps_packet_t *packet, void *src, size_t size)
{
	int ret;
	size_t offs, rlen = size;
	__PS_PACKET(packet)

	if (packet->flags & PS_PACKET_SIZE_SET) {
		if (packet->pos + size > header->size)
			return EINVAL;
	} else {
		if (packet->pos + size + sizeof(struct ps_packet_header_s) * 2 > state->size)
			return ENOBUFS;

		if ((ret = ps_packet_reserve(packet, packet->pos + size)))
			return ret;
	}

	offs = (packet->buffer_pos + sizeof(struct ps_packet_header_s) + packet->pos) % state->size;
	if (offs + size > state->size) {
		memcpy(&buffer->buffer[offs], src, state->size - offs);

		rlen -= state->size - offs;
		offs = 0;
		src = (void *) &((unsigned char *) src)[size - rlen];
	}

	memcpy(&buffer->buffer[offs], src, rlen);

	packet->pos += size;
	if (packet->pos > header->size)
		header->size = packet->pos;

	return 0;
}
