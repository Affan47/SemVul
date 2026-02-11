hnae_alloc_desc(struct hnae_ring *ring)
{
	int size = ring->desc_num * sizeof(ring->desc[0]);

	ring->desc = kzalloc(size, GFP_KERNEL);
	if (!ring->desc)
		return -ENOMEM;

	ring->desc_dma_addr = dma_map_single(ring_to_dev(ring),
		ring->desc, size, ring_to_dma_dir(ring));
	if (dma_mapping_error(ring_to_dev(ring), ring->desc_dma_addr)) {
		ring->desc_dma_addr = 0;
		kfree(ring->desc);
		ring->desc = NULL;
		return -ENOMEM;
	}

	return 0;
}
