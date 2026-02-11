qxl_ring_pop(struct qxl_ring *ring,
			 void *element)
{
	volatile struct qxl_ring_header *header = &(ring->ring->header);
	volatile uint8_t *ring_elt;
	int idx;
	unsigned long flags;
	spin_lock_irqsave(&ring->lock, flags);
	if (header->cons == header->prod) {
		header->notify_on_prod = header->cons + 1;
		spin_unlock_irqrestore(&ring->lock, flags);
		return false;
	}

	idx = header->cons & (ring->n_elements - 1);
	ring_elt = ring->ring->elements + idx * ring->element_size;

	memcpy(element, (void *)ring_elt, ring->element_size);

	header->cons++;

	spin_unlock_irqrestore(&ring->lock, flags);
	return true;
}
