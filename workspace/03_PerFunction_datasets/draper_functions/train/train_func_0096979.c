free_all_descbuffers(struct b43legacy_dmaring *ring)
{
	struct b43legacy_dmadesc_meta *meta;
	int i;

	if (!ring->used_slots)
		return;
	for (i = 0; i < ring->nr_slots; i++) {
		op32_idx2desc(ring, i, &meta);

		if (!meta->skb) {
			B43legacy_WARN_ON(!ring->tx);
			continue;
		}
		if (ring->tx)
			unmap_descbuffer(ring, meta->dmaaddr,
					 meta->skb->len, 1);
		else
			unmap_descbuffer(ring, meta->dmaaddr,
					 ring->rx_buffersize, 0);
		free_descriptor_buffer(ring, meta, 0);
	}
}
