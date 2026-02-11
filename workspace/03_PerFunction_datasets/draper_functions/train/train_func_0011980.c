cs5530_init_chip(void)
{
	struct pci_dev *master_0 = NULL, *cs5530_0 = NULL, *dev = NULL;

	while ((dev = pci_get_device(PCI_VENDOR_ID_CYRIX, PCI_ANY_ID, dev)) != NULL) {
		switch (dev->device) {
			case PCI_DEVICE_ID_CYRIX_PCI_MASTER:
				master_0 = pci_dev_get(dev);
				break;
			case PCI_DEVICE_ID_CYRIX_5530_LEGACY:
				cs5530_0 = pci_dev_get(dev);
				break;
		}
	}
	if (!master_0) {
		printk(KERN_ERR DRV_NAME ": unable to locate PCI MASTER function\n");
		goto fail_put;
	}
	if (!cs5530_0) {
		printk(KERN_ERR DRV_NAME ": unable to locate CS5530 LEGACY function\n");
		goto fail_put;
	}

	pci_set_master(cs5530_0);
	pci_try_set_mwi(cs5530_0);


	pci_write_config_byte(cs5530_0, PCI_CACHE_LINE_SIZE, 0x04);


	pci_write_config_word(cs5530_0, 0xd0, 0x5006);


	pci_write_config_byte(master_0, 0x40, 0x1e);


	pci_write_config_byte(master_0, 0x41, 0x14);


	pci_write_config_byte(master_0, 0x42, 0x00);
	pci_write_config_byte(master_0, 0x43, 0xc1);

	pci_dev_put(master_0);
	pci_dev_put(cs5530_0);
	return 0;
fail_put:
	pci_dev_put(master_0);
	pci_dev_put(cs5530_0);
	return -ENODEV;
}
