macb_open(struct net_device *dev)
{
	struct macb *bp = netdev_priv(dev);
	size_t bufsz = dev->mtu + ETH_HLEN + ETH_FCS_LEN + NET_IP_ALIGN;
	int err;

	netdev_dbg(bp->dev, "open\n");


	netif_carrier_off(dev);


	if (!bp->phy_dev)
		return -EAGAIN;


	macb_init_rx_buffer_size(bp, bufsz);

	err = macb_alloc_consistent(bp);
	if (err) {
		netdev_err(dev, "Unable to allocate DMA memory (error %d)\n",
			   err);
		return err;
	}

	napi_enable(&bp->napi);

	bp->macbgem_ops.mog_init_rings(bp);
	macb_init_hw(bp);


	phy_start(bp->phy_dev);

	netif_tx_start_all_queues(dev);

	return 0;
}
