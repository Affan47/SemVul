mptlan_remove(struct pci_dev *pdev)
{
	MPT_ADAPTER 		*ioc = pci_get_drvdata(pdev);
	struct net_device	*dev = ioc->netdev;

	if(dev != NULL) {
		unregister_netdev(dev);
		free_netdev(dev);
	}
}
