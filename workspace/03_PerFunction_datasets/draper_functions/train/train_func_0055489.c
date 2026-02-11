get_bound_vga(struct pci_dev *pci)
{
	struct pci_dev *p;


	switch (pci->vendor) {
	case PCI_VENDOR_ID_ATI:
	case PCI_VENDOR_ID_AMD:
	case PCI_VENDOR_ID_NVIDIA:
		if (pci->devfn == 1) {
			p = pci_get_domain_bus_and_slot(pci_domain_nr(pci->bus),
							pci->bus->number, 0);
			if (p) {
				if ((p->class >> 8) == PCI_CLASS_DISPLAY_VGA)
					return p;
				pci_dev_put(p);
			}
		}
		break;
	}
	return NULL;
}
