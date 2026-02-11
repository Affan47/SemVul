net2272_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct net2272 *dev;
	int ret;

	dev = net2272_probe_init(&pdev->dev, pdev->irq);
	if (IS_ERR(dev))
		return PTR_ERR(dev);
	dev->dev_id = pdev->device;

	if (pci_enable_device(pdev) < 0) {
		ret = -ENODEV;
		goto err_free;
	}

	pci_set_master(pdev);

	switch (pdev->device) {
	case PCI_DEVICE_ID_RDK1: ret = net2272_rdk1_probe(pdev, dev); break;
	case PCI_DEVICE_ID_RDK2: ret = net2272_rdk2_probe(pdev, dev); break;
	default: BUG();
	}
	if (ret)
		goto err_pci;

	ret = net2272_probe_fin(dev, 0);
	if (ret)
		goto err_pci;

	pci_set_drvdata(pdev, dev);

	return 0;

 err_pci:
	pci_disable_device(pdev);
 err_free:
	kfree(dev);

	return ret;
}
