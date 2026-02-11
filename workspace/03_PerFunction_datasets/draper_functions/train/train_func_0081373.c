pcie_bus_configure_set(struct pci_dev *dev, void *data)
{
	int mps, orig_mps;

	if (!pci_is_pcie(dev))
		return 0;

	if (pcie_bus_config == PCIE_BUS_TUNE_OFF ||
	    pcie_bus_config == PCIE_BUS_DEFAULT)
		return 0;

	mps = 128 << *(u8 *)data;
	orig_mps = pcie_get_mps(dev);

	pcie_write_mps(dev, mps);
	pcie_write_mrrs(dev);

	dev_info(&dev->dev, "Max Payload Size set to %4d/%4d (was %4d), Max Read Rq %4d\n",
		 pcie_get_mps(dev), 128 << dev->pcie_mpss,
		 orig_mps, pcie_get_readrq(dev));

	return 0;
}
