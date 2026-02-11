do_pci_probe(void)
{
	struct pci_dev *my_dev;

	my_dev = pci_get_device(PCI_VENDOR_ID_ATI,
				PCI_DEVICE_ID_ATI_264VT, NULL);
	if (my_dev) {
		pr_err("Using device: %s\n", pci_name(my_dev));
		pci_addr_phys = 0;
		if (my_dev->resource[0].flags & IORESOURCE_MEM) {
			pci_addr_phys = my_dev->resource[0].start;
			pr_info("memory at %pa\n", &pci_addr_phys);
		}
		if (pci_addr_phys == 0) {
			pr_err("no memory resource ?\n");
			pci_dev_put(my_dev);
			return NULL;
		}
	} else {
		pr_err("pci_probe failed\n");
		return NULL;
	}
	return my_dev;
}
