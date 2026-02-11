pcnet32_set_multicast_list(struct net_device *dev)
{
	unsigned long ioaddr = dev->base_addr, flags;
	struct pcnet32_private *lp = netdev_priv(dev);
	int csr15, suspended;

	spin_lock_irqsave(&lp->lock, flags);
	suspended = pcnet32_suspend(dev, &flags, 0);
	csr15 = lp->a->read_csr(ioaddr, CSR15);
	if (dev->flags & IFF_PROMISC) {

		netif_info(lp, hw, dev, "Promiscuous mode enabled\n");
		lp->init_block->mode =
		    cpu_to_le16(0x8000 | (lp->options & PCNET32_PORT_PORTSEL) <<
				7);
		lp->a->write_csr(ioaddr, CSR15, csr15 | 0x8000);
	} else {
		lp->init_block->mode =
		    cpu_to_le16((lp->options & PCNET32_PORT_PORTSEL) << 7);
		lp->a->write_csr(ioaddr, CSR15, csr15 & 0x7fff);
		pcnet32_load_multicast(dev);
	}

	if (suspended) {
		int csr5;

		csr5 = lp->a->read_csr(ioaddr, CSR5);
		lp->a->write_csr(ioaddr, CSR5, csr5 & (~CSR5_SUSPEND));
	} else {
		lp->a->write_csr(ioaddr, CSR0, CSR0_STOP);
		pcnet32_restart(dev, CSR0_NORMAL);
		netif_wake_queue(dev);
	}

	spin_unlock_irqrestore(&lp->lock, flags);
}
