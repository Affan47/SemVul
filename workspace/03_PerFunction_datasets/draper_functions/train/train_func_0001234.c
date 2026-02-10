bna_rx_coalescing_timeo_set(struct bna_rx *rx, int coalescing_timeo)
{
	struct bna_rxp *rxp;

	list_for_each_entry(rxp, &rx->rxp_q, qe) {
		rxp->cq.ccb->rx_coalescing_timeo = coalescing_timeo;
		bna_ib_coalescing_timeo_set(&rxp->cq.ib, coalescing_timeo);
	}
}
