vortex_suspend(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct net_device *ndev = pci_get_drvdata(pdev);

	if (!ndev || !netif_running(ndev))
		return 0;

	netif_device_detach(ndev);
	vortex_down(ndev, 1);

	return 0;
}
