ps_packet_dma(ps_packet_t *packet, void **mem, size_t size, ps_flags_t flags)
{
	int ret;
	struct ps_fake_dma_s *fake_dma;
	size_t offs;
	__PS_PACKET(packet)

	if ((packet->flags & PS_PACKET_SIZE_SET) | (packet->flags & PS_PACKET_READ)) {
		if (packet->pos + size > header->size)
			return EINVAL;
	} else if (packet->pos + size + sizeof(struct ps_packet_header_s) * 2 > state->size)
		return ENOBUFS;

	offs = (packet->buffer_pos + sizeof(struct ps_packet_header_s) + packet->pos) % state->size;

	if (offs + size <= state->size) {

		if ((!(packet->flags & PS_PACKET_SIZE_SET)) && (packet->flags & PS_PACKET_WRITE)) {
			if ((ret = ps_packet_reserve(packet, packet->pos + size)))
				return ret;
		}
		*mem = &buffer->buffer[offs];

		packet->pos += size;
		if ((!(packet->flags & PS_PACKET_SIZE_SET)) && (packet->flags & PS_PACKET_WRITE) && (packet->pos > header->size))
			header->size = packet->pos;

		return 0;
	}

	if (!(flags & PS_ACCEPT_FAKE_DMA))
		return EAGAIN;


	if ((!(packet->flags & PS_PACKET_SIZE_SET)) && (packet->flags & PS_PACKET_WRITE)) {
		if ((ret = ps_packet_reserve(packet, packet->pos + size)))
			return ret;
	}

	if ((ret = ps_packet_fakedma_alloc(packet, &fake_dma, size)))
		return ret;

	fake_dma->size = size;
	fake_dma->pos = packet->pos;

	if (packet->flags & PS_PACKET_READ) {
		if ((ret = ps_packet_read(packet, fake_dma->mem, size))) {
			ps_packet_fakedma_free(packet, fake_dma);
			return ret;
		}
	}

	*mem = fake_dma->mem;

	packet->pos += size;
	if ((!(packet->flags & PS_PACKET_SIZE_SET)) && (packet->flags & PS_PACKET_WRITE) && (packet->pos > header->size))
		header->size = packet->pos;

	return 0;
}
