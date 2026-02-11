ns83820_open(struct net_device *ndev)
{
	struct ns83820 *dev = PRIV(ndev);
	unsigned i;
	u32 desc;
	int ret;

	dprintk("ns83820_open\n");

	writel(0, dev->base + PQCR);

	ret = ns83820_setup_rx(ndev);
	if (ret)
		goto failed;

	memset(dev->tx_descs, 0, 4 * NR_TX_DESC * DESC_SIZE);
	for (i=0; i<NR_TX_DESC; i++) {
		dev->tx_descs[(i * DESC_SIZE) + DESC_LINK]
				= cpu_to_le32(
				  dev->tx_phy_descs
				  + ((i+1) % NR_TX_DESC) * DESC_SIZE * 4);
	}

	dev->tx_idx = 0;
	dev->tx_done_idx = 0;
	desc = dev->tx_phy_descs;
	writel(0, dev->base + TXDP_HI);
	writel(desc, dev->base + TXDP);

	init_timer(&dev->tx_watchdog);
	dev->tx_watchdog.data = (unsigned long)ndev;
	dev->tx_watchdog.function = ns83820_tx_watch;
	mod_timer(&dev->tx_watchdog, jiffies + 2*HZ);

	netif_start_queue(ndev);

	return 0;

failed:
	ns83820_stop(ndev);
	return ret;
}
