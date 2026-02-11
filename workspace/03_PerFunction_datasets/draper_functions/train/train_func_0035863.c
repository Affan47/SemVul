ssb_pcihost_resume(struct device *d)
{
	struct pci_dev *dev = to_pci_dev(d);
	struct ssb_bus *ssb = pci_get_drvdata(dev);
	int err;

	pci_back_from_sleep(dev);
	err = pci_enable_device(dev);
	if (err)
		return err;
	pci_restore_state(dev);
	err = ssb_bus_resume(ssb);
	if (err)
		return err;

	return 0;
}
