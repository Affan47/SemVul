bnx2_has_fast_work(struct bnx2_napi *bnapi)
{
	struct bnx2_tx_ring_info *txr = &bnapi->tx_ring;
	struct bnx2_rx_ring_info *rxr = &bnapi->rx_ring;

	if ((bnx2_get_hw_rx_cons(bnapi) != rxr->rx_cons) ||
	    (bnx2_get_hw_tx_cons(bnapi) != txr->hw_tx_cons))
		return 1;
	return 0;
}
