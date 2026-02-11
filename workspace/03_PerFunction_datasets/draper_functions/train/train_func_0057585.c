ne2k_pci_resume (struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata (pdev);
	int rc;

	pci_set_power_state(pdev, PCI_D0);
	pci_restore_state(pdev);

	rc = pci_enable_device(pdev);
	if (rc)
		return rc;

	NS8390_init(dev, 1);
	netif_device_attach(dev);

	return 0;
}
