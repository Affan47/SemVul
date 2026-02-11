ide_generic_check_pci_legacy_iobases(int *primary, int *secondary)
{
#ifdef CONFIG_PCI
	struct pci_dev *p = NULL;
	u16 val;

	for_each_pci_dev(p) {
		if (pci_resource_start(p, 0) == 0x1f0)
			*primary = 1;
		if (pci_resource_start(p, 2) == 0x170)
			*secondary = 1;


		if (p->vendor == PCI_VENDOR_ID_CYRIX &&
		    (p->device == PCI_DEVICE_ID_CYRIX_5510 ||
		     p->device == PCI_DEVICE_ID_CYRIX_5520))
			*primary = *secondary = 1;


		if (p->vendor == PCI_VENDOR_ID_INTEL &&
		    p->device == PCI_DEVICE_ID_INTEL_82371MX) {
			pci_read_config_word(p, 0x6C, &val);
			if (val & 0x8000) {

				if (val & 0x4000)
					*secondary = 1;
				else
					*primary = 1;
			}
		}
	}
#endif
}
