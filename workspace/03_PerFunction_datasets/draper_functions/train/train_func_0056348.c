pci_legacy_resume(struct device *dev)
{
	struct pci_dev *pci_dev = to_pci_dev(dev);
	struct pci_driver *drv = pci_dev->driver;

	pci_fixup_device(pci_fixup_resume, pci_dev);

	return drv && drv->resume ?
			drv->resume(pci_dev) : pci_pm_reenable_device(pci_dev);
}
