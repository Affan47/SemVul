xgene_enet_setup_ring(
				    struct xgene_enet_desc_ring *ring)
{
	bool is_bufpool;
	u32 addr, i;

	xgene_enet_clr_ring_state(ring);
	xgene_enet_set_ring_state(ring);
	xgene_enet_set_ring_id(ring);

	ring->slots = xgene_enet_get_numslots(ring->id, ring->size);

	is_bufpool = xgene_enet_is_bufpool(ring->id);
	if (is_bufpool || xgene_enet_ring_owner(ring->id) != RING_OWNER_CPU)
		return ring;

	addr = CSR_VMID0_INTR_MBOX + (4 * (ring->id & RING_BUFNUM_MASK));
	xgene_enet_ring_wr32(ring, addr, ring->irq_mbox_dma >> 10);

	for (i = 0; i < ring->slots; i++)
		xgene_enet_mark_desc_slot_empty(&ring->raw_desc[i]);

	return ring;
}
