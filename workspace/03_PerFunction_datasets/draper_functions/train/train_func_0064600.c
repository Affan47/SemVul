enable_pci_ports(void)
{
#if defined(CONFIG_PCI)
	struct pci_dev *dev = NULL;

	while ((dev = pci_get_class(PCI_CLASS_STORAGE_SCSI << 8, dev))) {
#if defined(DEBUG_PCI_DETECT)
		printk("%s: enable_pci_ports, bus %d, devfn 0x%x.\n",
		       driver_name, dev->bus->number, dev->devfn);
#endif

		if (pci_enable_device(dev))
			printk
			    ("%s: warning, pci_enable_device failed, bus %d devfn 0x%x.\n",
			     driver_name, dev->bus->number, dev->devfn);
	}

#endif
}
