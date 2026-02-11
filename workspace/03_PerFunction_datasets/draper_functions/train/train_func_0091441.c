pci_probe ( struct pci_device *pci ) {
	int rc;

	DBGC ( pci, PCI_FMT " (%04x:%04x) has driver \"%s\"\n",
	       PCI_ARGS ( pci ), pci->vendor, pci->device, pci->id->name );
	DBGC ( pci, PCI_FMT " has mem %lx io %lx irq %d\n",
	       PCI_ARGS ( pci ), pci->membase, pci->ioaddr, pci->irq );

	if ( ( rc = pci->driver->probe ( pci ) ) != 0 ) {
		DBGC ( pci, PCI_FMT " probe failed: %s\n",
		       PCI_ARGS ( pci ), strerror ( rc ) );
		return rc;
	}

	return 0;
}
