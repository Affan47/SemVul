ring_write_descriptors(struct tb_ring *ring)
{
	struct ring_frame *frame, *n;
	struct ring_desc *descriptor;
	list_for_each_entry_safe(frame, n, &ring->queue, list) {
		if (ring_full(ring))
			break;
		list_move_tail(&frame->list, &ring->in_flight);
		descriptor = &ring->descriptors[ring->head];
		descriptor->phys = frame->buffer_phy;
		descriptor->time = 0;
		descriptor->flags = RING_DESC_POSTED | RING_DESC_INTERRUPT;
		if (ring->is_tx) {
			descriptor->length = frame->size;
			descriptor->eof = frame->eof;
			descriptor->sof = frame->sof;
		}
		ring->head = (ring->head + 1) % ring->size;
		ring_iowrite16desc(ring, ring->head, ring->is_tx ? 10 : 8);
	}
}
