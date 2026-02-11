cr_pll_init(void)
{
	int err;
	u32 dev_en;

	mch_dev = pci_get_device(PCI_VENDOR_ID_INTEL,
					CRVML_DEVICE_MCH, NULL);
	if (!mch_dev) {
		printk(KERN_ERR
		       "Could not find Carillo Ranch MCH device.\n");
		return -ENODEV;
	}

	pci_read_config_dword(mch_dev, CRVML_REG_MCHEN, &dev_en);
	if (!(dev_en & CRVML_MCHEN_BIT)) {
		printk(KERN_ERR
		       "Carillo Ranch MCH device was not enabled.\n");
		pci_dev_put(mch_dev);
		return -ENODEV;
	}

	pci_read_config_dword(mch_dev, CRVML_REG_MCHBAR,
			      &mch_bar);
	mch_regs_base =
	    ioremap_nocache(mch_bar, CRVML_MCHMAP_SIZE);
	if (!mch_regs_base) {
		printk(KERN_ERR
		       "Carillo Ranch MCH device was not enabled.\n");
		pci_dev_put(mch_dev);
		return -ENODEV;
	}

	err = vmlfb_register_subsys(&cr_pll_ops);
	if (err) {
		printk(KERN_ERR
		       "Carillo Ranch failed to initialize vml_sys.\n");
		pci_dev_put(mch_dev);
		return err;
	}

	return 0;
}
