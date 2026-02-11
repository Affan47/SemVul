init_registers(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	void __iomem * ioaddr = ns_ioaddr(dev);

	init_phy_fixup(dev);


	readl(ioaddr + IntrStatus);

	writel(np->ring_dma, ioaddr + RxRingPtr);
	writel(np->ring_dma + RX_RING_SIZE * sizeof(struct netdev_desc),
		ioaddr + TxRingPtr);


	np->tx_config = TxAutoPad | TxCollRetry | TxMxdma_256 |
				TX_FLTH_VAL | TX_DRTH_VAL_START;
	writel(np->tx_config, ioaddr + TxConfig);


	np->rx_config = RxMxdma_256 | RX_DRTH_VAL;

	if (np->rx_buf_sz > NATSEMI_LONGPKT)
		np->rx_config |= RxAcceptLong;

	writel(np->rx_config, ioaddr + RxConfig);


	np->SavedClkRun = readl(ioaddr + ClkRun);
	writel(np->SavedClkRun & ~PMEEnable, ioaddr + ClkRun);
	if (np->SavedClkRun & PMEStatus && netif_msg_wol(np)) {
		printk(KERN_NOTICE "%s: Wake-up event %#08x\n",
			dev->name, readl(ioaddr + WOLCmd));
	}

	check_link(dev);
	__set_rx_mode(dev);


	writel(DEFAULT_INTR, ioaddr + IntrMask);
	natsemi_irq_enable(dev);

	writel(RxOn | TxOn, ioaddr + ChipCmd);
	writel(StatsClear, ioaddr + StatsCtrl);
}
