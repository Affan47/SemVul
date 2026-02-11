bnxt_tx_disable(struct bnxt *bp)
{
	int i;
	struct bnxt_tx_ring_info *txr;
	struct netdev_queue *txq;

	if (bp->tx_ring) {
		for (i = 0; i < bp->tx_nr_rings; i++) {
			txr = &bp->tx_ring[i];
			txq = netdev_get_tx_queue(bp->dev, i);
			txr->dev_state = BNXT_DEV_STATE_CLOSING;
		}
	}

	netif_tx_disable(bp->dev);
	netif_carrier_off(bp->dev);
}
