pci_pm_reenable_device(struct pci_dev *pci_dev)
{
	int retval;


	retval = pci_reenable_device(pci_dev);


	if (pci_dev->is_busmaster)
		pci_set_master(pci_dev);

	return retval;
}
