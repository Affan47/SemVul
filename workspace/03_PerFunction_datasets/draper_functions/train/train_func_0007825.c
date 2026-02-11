epic_tx_timeout(struct net_device *dev)
{
	struct epic_private *ep = netdev_priv(dev);
	void __iomem *ioaddr = ep->ioaddr;

	if (debug > 0) {
		netdev_warn(dev, "Transmit timeout using MII device, Tx status %4.4x.\n",
			    er16(TxSTAT));
		if (debug > 1) {
			netdev_dbg(dev, "Tx indices: dirty_tx %d, cur_tx %d.\n",
				   ep->dirty_tx, ep->cur_tx);
		}
	}
	if (er16(TxSTAT) & 0x10) {
		dev->stats.tx_fifo_errors++;
		ew32(COMMAND, RestartTx);
	} else {
		epic_restart(dev);
		ew32(COMMAND, TxQueued);
	}

	dev->trans_start = jiffies;
	dev->stats.tx_errors++;
	if (!ep->tx_full)
		netif_wake_queue(dev);
}
