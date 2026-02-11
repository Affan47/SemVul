bcm_sysport_tx_poll(struct napi_struct *napi, int budget)
{
	struct bcm_sysport_tx_ring *ring =
		container_of(napi, struct bcm_sysport_tx_ring, napi);
	unsigned int work_done = 0;

	work_done = bcm_sysport_tx_reclaim(ring->priv, ring);

	if (work_done == 0) {
		napi_complete(napi);

		intrl2_1_mask_clear(ring->priv, BIT(ring->index));

		return 0;
	}

	return budget;
}
