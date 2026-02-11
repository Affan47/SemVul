zt5550_hc_config(struct pci_dev *pdev)
{
	int ret;


	if (hc_dev) {
		err("too many host controller devices?");
		return -EBUSY;
	}

	ret = pci_enable_device(pdev);
	if (ret) {
		err("cannot enable %s\n", pci_name(pdev));
		return ret;
	}

	hc_dev = pdev;
	dbg("hc_dev = %p", hc_dev);
	dbg("pci resource start %llx", (unsigned long long)pci_resource_start(hc_dev, 1));
	dbg("pci resource len %llx", (unsigned long long)pci_resource_len(hc_dev, 1));

	if (!request_mem_region(pci_resource_start(hc_dev, 1),
				pci_resource_len(hc_dev, 1), MY_NAME)) {
		err("cannot reserve MMIO region");
		ret = -ENOMEM;
		goto exit_disable_device;
	}

	hc_registers =
	    ioremap(pci_resource_start(hc_dev, 1), pci_resource_len(hc_dev, 1));
	if (!hc_registers) {
		err("cannot remap MMIO region %llx @ %llx",
			(unsigned long long)pci_resource_len(hc_dev, 1),
			(unsigned long long)pci_resource_start(hc_dev, 1));
		ret = -ENODEV;
		goto exit_release_region;
	}

	csr_hc_index = hc_registers + CSR_HCINDEX;
	csr_hc_data = hc_registers + CSR_HCDATA;
	csr_int_status = hc_registers + CSR_INTSTAT;
	csr_int_mask = hc_registers + CSR_INTMASK;


	dbg("disabling host control, fault and serial interrupts");
	writeb((u8) HC_INT_MASK_REG, csr_hc_index);
	writeb((u8) ALL_INDEXED_INTS_MASK, csr_hc_data);
	dbg("disabled host control, fault and serial interrupts");


	dbg("disabling timer0, timer1 and ENUM interrupts");
	writeb((u8) ALL_DIRECT_INTS_MASK, csr_int_mask);
	dbg("disabled timer0, timer1 and ENUM interrupts");
	return 0;

exit_release_region:
	release_mem_region(pci_resource_start(hc_dev, 1),
			   pci_resource_len(hc_dev, 1));
exit_disable_device:
	pci_disable_device(hc_dev);
	return ret;
}
