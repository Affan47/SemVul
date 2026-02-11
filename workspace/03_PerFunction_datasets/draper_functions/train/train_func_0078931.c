axnet_tx_timeout(struct net_device *dev)
{
	long e8390_base = dev->base_addr;
	struct ei_device *ei_local = netdev_priv(dev);
	int txsr, isr, tickssofar = jiffies - dev_trans_start(dev);
	unsigned long flags;

	dev->stats.tx_errors++;

	spin_lock_irqsave(&ei_local->page_lock, flags);
	txsr = inb(e8390_base+EN0_TSR);
	isr = inb(e8390_base+EN0_ISR);
	spin_unlock_irqrestore(&ei_local->page_lock, flags);

	netdev_dbg(dev, "Tx timed out, %s TSR=%#2x, ISR=%#2x, t=%d.\n",
		   (txsr & ENTSR_ABT) ? "excess collisions." :
		   (isr) ? "lost interrupt?" : "cable problem?",
		   txsr, isr, tickssofar);

	if (!isr && !dev->stats.tx_packets)
	{

		ei_local->interface_num ^= 1;
	}


	spin_lock_irqsave(&ei_local->page_lock, flags);


	ei_reset_8390(dev);
	AX88190_init(dev, 1);

	spin_unlock_irqrestore(&ei_local->page_lock, flags);
	netif_wake_queue(dev);
}
