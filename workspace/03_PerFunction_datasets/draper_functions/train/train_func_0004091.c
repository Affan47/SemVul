epic_suspend (struct pci_dev *pdev, pm_message_t state)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct epic_private *ep = netdev_priv(dev);
	void __iomem *ioaddr = ep->ioaddr;

	if (!netif_running(dev))
		return 0;
	epic_pause(dev);

	ew32(GENCTL, 0x0008);

	return 0;
}
