el3_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *) dev_id;
	struct el3_private *lp = netdev_priv(dev);
	unsigned int ioaddr;
	__u16 status;
	int i = 0, handled = 1;

	if (!netif_device_present(dev))
		return IRQ_NONE;

	ioaddr = dev->base_addr;

	netdev_dbg(dev, "interrupt, status %4.4x.\n", inw(ioaddr + EL3_STATUS));

	spin_lock(&lp->lock);
	while ((status = inw(ioaddr + EL3_STATUS)) &
	(IntLatch | RxComplete | StatsFull)) {
		if ((status & 0xe000) != 0x2000) {
			netdev_dbg(dev, "interrupt from dead card\n");
			handled = 0;
			break;
		}
		if (status & RxComplete)
			el3_rx(dev);
		if (status & TxAvailable) {
			netdev_dbg(dev, "    TX room bit was handled.\n");

			outw(AckIntr | TxAvailable, ioaddr + EL3_CMD);
			netif_wake_queue(dev);
		}
		if (status & TxComplete)
			pop_tx_status(dev);
		if (status & (AdapterFailure | RxEarly | StatsFull)) {

			if (status & StatsFull)
				update_stats(dev);
			if (status & RxEarly) {

				el3_rx(dev);
				outw(AckIntr | RxEarly, ioaddr + EL3_CMD);
			}
			if (status & AdapterFailure) {
				u16 fifo_diag;
				EL3WINDOW(4);
				fifo_diag = inw(ioaddr + 4);
				EL3WINDOW(1);
				netdev_warn(dev, "adapter failure, FIFO diagnostic register %04x.\n",
			    fifo_diag);
				if (fifo_diag & 0x0400) {

					tc589_wait_for_completion(dev, TxReset);
					outw(TxEnable, ioaddr + EL3_CMD);
				}
				if (fifo_diag & 0x2000) {

					tc589_wait_for_completion(dev, RxReset);
					set_rx_mode(dev);
					outw(RxEnable, ioaddr + EL3_CMD);
				}
				outw(AckIntr | AdapterFailure, ioaddr + EL3_CMD);
			}
		}
		if (++i > 10) {
			netdev_err(dev, "infinite loop in interrupt, status %4.4x.\n",
					status);

			outw(AckIntr | 0xFF, ioaddr + EL3_CMD);
			break;
		}

		outw(AckIntr | IntReq | IntLatch, ioaddr + EL3_CMD);
	}
	lp->last_irq = jiffies;
	spin_unlock(&lp->lock);
	netdev_dbg(dev, "exiting interrupt, status %4.4x.\n",
			inw(ioaddr + EL3_STATUS));
	return IRQ_RETVAL(handled);
}
