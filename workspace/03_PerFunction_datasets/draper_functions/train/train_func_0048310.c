xgene_enet_clear_ring(struct xgene_enet_desc_ring *ring)
{
	u32 data;
	bool is_bufpool;

	is_bufpool = xgene_enet_is_bufpool(ring->id);
	if (is_bufpool || xgene_enet_ring_owner(ring->id) != RING_OWNER_CPU)
		goto out;

	xgene_enet_ring_rd32(ring, CSR_RING_NE_INT_MODE, &data);
	data &= ~BIT(31 - xgene_enet_ring_bufnum(ring->id));
	xgene_enet_ring_wr32(ring, CSR_RING_NE_INT_MODE, data);

out:
	xgene_enet_clr_desc_ring_id(ring);
	xgene_enet_clr_ring_state(ring);
}
