de4x5_rst_desc_ring(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    int i;
    s32 omr;

    if (lp->cache.save_cnt) {
	STOP_DE4X5;
	outl(lp->dma_rings, DE4X5_RRBA);
	outl(lp->dma_rings + NUM_RX_DESC * sizeof(struct de4x5_desc),
	     DE4X5_TRBA);

	lp->rx_new = lp->rx_old = 0;
	lp->tx_new = lp->tx_old = 0;

	for (i = 0; i < lp->rxRingSize; i++) {
	    lp->rx_ring[i].status = cpu_to_le32(R_OWN);
	}

	for (i = 0; i < lp->txRingSize; i++) {
	    lp->tx_ring[i].status = cpu_to_le32(0);
	}

	barrier();
	lp->cache.save_cnt--;
	START_DE4X5;
    }
}
