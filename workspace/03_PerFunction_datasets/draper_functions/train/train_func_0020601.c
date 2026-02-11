netdev_error(struct net_device *dev, int intr_status)
{
	struct netdev_private *np = netdev_priv(dev);
	void __iomem * ioaddr = ns_ioaddr(dev);

	spin_lock(&np->lock);
	if (intr_status & LinkChange) {
		u16 lpa = mdio_read(dev, MII_LPA);
		if (mdio_read(dev, MII_BMCR) & BMCR_ANENABLE &&
		    netif_msg_link(np)) {
			printk(KERN_INFO
				"%s: Autonegotiation advertising"
				" %#04x  partner %#04x.\n", dev->name,
				np->advertising, lpa);
		}


		readw(ioaddr + MIntrStatus);
		check_link(dev);
	}
	if (intr_status & StatsMax) {
		__get_stats(dev);
	}
	if (intr_status & IntrTxUnderrun) {
		if ((np->tx_config & TxDrthMask) < TX_DRTH_VAL_LIMIT) {
			np->tx_config += TX_DRTH_VAL_INC;
			if (netif_msg_tx_err(np))
				printk(KERN_NOTICE
					"%s: increased tx threshold, txcfg %#08x.\n",
					dev->name, np->tx_config);
		} else {
			if (netif_msg_tx_err(np))
				printk(KERN_NOTICE
					"%s: tx underrun with maximum tx threshold, txcfg %#08x.\n",
					dev->name, np->tx_config);
		}
		writel(np->tx_config, ioaddr + TxConfig);
	}
	if (intr_status & WOLPkt && netif_msg_wol(np)) {
		int wol_status = readl(ioaddr + WOLCmd);
		printk(KERN_NOTICE "%s: Link wake-up event %#08x\n",
			dev->name, wol_status);
	}
	if (intr_status & RxStatusFIFOOver) {
		if (netif_msg_rx_err(np) && netif_msg_intr(np)) {
			printk(KERN_NOTICE "%s: Rx status FIFO overrun\n",
				dev->name);
		}
		dev->stats.rx_fifo_errors++;
		dev->stats.rx_errors++;
	}

	if (intr_status & IntrPCIErr) {
		printk(KERN_NOTICE "%s: PCI error %#08x\n", dev->name,
			intr_status & IntrPCIErr);
		dev->stats.tx_fifo_errors++;
		dev->stats.tx_errors++;
		dev->stats.rx_fifo_errors++;
		dev->stats.rx_errors++;
	}
	spin_unlock(&np->lock);
}
