bnxt_poll_controller(struct net_device *dev)
{
	struct bnxt *bp = netdev_priv(dev);
	int i;


	for (i = 0; i < bp->tx_nr_rings; i++) {
		struct bnxt_tx_ring_info *txr = &bp->tx_ring[i];

		napi_schedule(&txr->bnapi->napi);
	}
}
