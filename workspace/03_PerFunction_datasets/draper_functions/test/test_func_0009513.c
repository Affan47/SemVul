pcnet32_restart(struct net_device *dev, unsigned int csr0_bits)
{
	struct pcnet32_private *lp = netdev_priv(dev);
	unsigned long ioaddr = dev->base_addr;
	int i;


	for (i = 0; i < 100; i++)
		if (lp->a->read_csr(ioaddr, CSR0) & CSR0_STOP)
			break;

	if (i >= 100)
		netif_err(lp, drv, dev, "%s timed out waiting for stop\n",
			  __func__);

	pcnet32_purge_tx_ring(dev);
	if (pcnet32_init_ring(dev))
		return;


	lp->a->write_csr(ioaddr, CSR0, CSR0_INIT);
	i = 0;
	while (i++ < 1000)
		if (lp->a->read_csr(ioaddr, CSR0) & CSR0_IDON)
			break;

	lp->a->write_csr(ioaddr, CSR0, csr0_bits);
}
