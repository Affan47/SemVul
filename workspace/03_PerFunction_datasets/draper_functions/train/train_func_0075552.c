a4t_pci_probe(struct pci_dev *dev_a4t, struct IsdnCardState *cs,
			 u_int *found, u_int *pci_memaddr)
{
	u16 sub_sys;
	u16 sub_vendor;

	sub_vendor = dev_a4t->subsystem_vendor;
	sub_sys = dev_a4t->subsystem_device;
	if ((sub_sys == PCI_DEVICE_ID_BERKOM_A4T) && (sub_vendor == PCI_VENDOR_ID_BERKOM)) {
		if (pci_enable_device(dev_a4t))
			return (0);
		*found = 1;
		*pci_memaddr = pci_resource_start(dev_a4t, 0);
		cs->irq = dev_a4t->irq;
		return (1);
	}

	return (-1);
}
