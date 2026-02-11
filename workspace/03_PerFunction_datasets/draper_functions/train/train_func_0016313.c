hpwdt_init_one(struct pci_dev *dev,
					const struct pci_device_id *ent)
{
	int retval;


	hpwdt_check_nmi_decoding(dev);


	if (dev->subsystem_vendor != PCI_VENDOR_ID_HP) {
		dev_warn(&dev->dev,
			"This server does not have an iLO2+ ASIC.\n");
		return -ENODEV;
	}


	if (dev->subsystem_device == 0x1979)
		return -ENODEV;

	if (pci_enable_device(dev)) {
		dev_warn(&dev->dev,
			"Not possible to enable PCI Device: 0x%x:0x%x.\n",
			ent->vendor, ent->device);
		return -ENODEV;
	}

	pci_mem_addr = pci_iomap(dev, 1, 0x80);
	if (!pci_mem_addr) {
		dev_warn(&dev->dev,
			"Unable to detect the iLO2+ server memory.\n");
		retval = -ENOMEM;
		goto error_pci_iomap;
	}
	hpwdt_timer_reg = pci_mem_addr + 0x70;
	hpwdt_timer_con = pci_mem_addr + 0x72;


	hpwdt_stop();


	if (hpwdt_change_timer(soft_margin))
		hpwdt_change_timer(DEFAULT_MARGIN);


	retval = hpwdt_init_nmi_decoding(dev);
	if (retval != 0)
		goto error_init_nmi_decoding;

	retval = misc_register(&hpwdt_miscdev);
	if (retval < 0) {
		dev_warn(&dev->dev,
			"Unable to register miscdev on minor=%d (err=%d).\n",
			WATCHDOG_MINOR, retval);
		goto error_misc_register;
	}

	dev_info(&dev->dev, "HP Watchdog Timer Driver: %s"
			", timer margin: %d seconds (nowayout=%d).\n",
			HPWDT_VERSION, soft_margin, nowayout);
	return 0;

error_misc_register:
	hpwdt_exit_nmi_decoding();
error_init_nmi_decoding:
	pci_iounmap(dev, pci_mem_addr);
error_pci_iomap:
	pci_disable_device(dev);
	return retval;
}
