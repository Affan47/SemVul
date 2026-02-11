ace_init_cleanup(struct net_device *dev)
{
	struct ace_private *ap;

	ap = netdev_priv(dev);

	ace_free_descriptors(dev);

	if (ap->info)
		pci_free_consistent(ap->pdev, sizeof(struct ace_info),
				    ap->info, ap->info_dma);
	kfree(ap->skb);
	kfree(ap->trace_buf);

	if (dev->irq)
		free_irq(dev->irq, dev);

	iounmap(ap->regs);
}
