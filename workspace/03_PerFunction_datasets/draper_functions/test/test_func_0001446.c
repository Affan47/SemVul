vt8237_force_enable_hpet(struct pci_dev *dev)
{
	u32 uninitialized_var(val);

	if (hpet_address || force_hpet_address)
		return;

	if (!hpet_force_user) {
		hpet_print_force_info();
		return;
	}

	pci_read_config_dword(dev, 0x68, &val);


	if (val & 0x80) {
		force_hpet_address = (val & ~0x3ff);
		dev_printk(KERN_DEBUG, &dev->dev, "HPET at 0x%lx\n",
			force_hpet_address);
		return;
	}


	val = 0xfed00000 | 0x80;
	pci_write_config_dword(dev, 0x68, val);

	pci_read_config_dword(dev, 0x68, &val);
	if (val & 0x80) {
		force_hpet_address = (val & ~0x3ff);
		dev_printk(KERN_DEBUG, &dev->dev, "Force enabled HPET at "
			"0x%lx\n", force_hpet_address);
		cached_dev = dev;
		force_hpet_resume_type = VT8237_FORCE_HPET_RESUME;
		return;
	}

	dev_printk(KERN_DEBUG, &dev->dev, "Failed to force enable HPET\n");
}
