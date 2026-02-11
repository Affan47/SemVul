usb_amd_find_chipset_info(void)
{
	unsigned long flags;
	struct amd_chipset_info info;
	int ret;

	spin_lock_irqsave(&amd_lock, flags);


	if (amd_chipset.probe_count > 0) {
		amd_chipset.probe_count++;
		spin_unlock_irqrestore(&amd_lock, flags);
		return amd_chipset.probe_result;
	}
	memset(&info, 0, sizeof(info));
	spin_unlock_irqrestore(&amd_lock, flags);

	if (!amd_chipset_sb_type_init(&info)) {
		ret = 0;
		goto commit;
	}


	if (info.sb_type.gen == AMD_CHIPSET_UNKNOWN ||
			info.sb_type.gen == AMD_CHIPSET_SB600 ||
			info.sb_type.gen == AMD_CHIPSET_YANGTZE ||
			(info.sb_type.gen == AMD_CHIPSET_SB700 &&
			info.sb_type.rev > 0x3b)) {
		if (info.smbus_dev) {
			pci_dev_put(info.smbus_dev);
			info.smbus_dev = NULL;
		}
		ret = 0;
		goto commit;
	}

	info.nb_dev = pci_get_device(PCI_VENDOR_ID_AMD, 0x9601, NULL);
	if (info.nb_dev) {
		info.nb_type = 1;
	} else {
		info.nb_dev = pci_get_device(PCI_VENDOR_ID_AMD, 0x1510, NULL);
		if (info.nb_dev) {
			info.nb_type = 2;
		} else {
			info.nb_dev = pci_get_device(PCI_VENDOR_ID_AMD,
						     0x9600, NULL);
			if (info.nb_dev)
				info.nb_type = 3;
		}
	}

	ret = info.probe_result = 1;
	printk(KERN_DEBUG "QUIRK: Enable AMD PLL fix\n");

commit:

	spin_lock_irqsave(&amd_lock, flags);
	if (amd_chipset.probe_count > 0) {


		amd_chipset.probe_count++;
		ret = amd_chipset.probe_result;

		spin_unlock_irqrestore(&amd_lock, flags);

		pci_dev_put(info.nb_dev);
		pci_dev_put(info.smbus_dev);

	} else {

		info.probe_count++;
		amd_chipset = info;
		spin_unlock_irqrestore(&amd_lock, flags);
	}

	return ret;
}
