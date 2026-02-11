pci_read_config ( struct pci_device *pci ) {
	uint16_t busdevfn;
	uint8_t hdrtype;
	uint32_t tmp;


	if ( PCI_FUNC ( pci->busdevfn ) != 0 ) {
		busdevfn = pci->busdevfn;
		pci->busdevfn = PCI_FIRST_FUNC ( pci->busdevfn );
		pci_read_config_byte ( pci, PCI_HEADER_TYPE, &hdrtype );
		pci->busdevfn = busdevfn;
		if ( ! ( hdrtype & 0x80 ) )
			return -ENODEV;
	}


	pci_read_config_dword ( pci, PCI_VENDOR_ID, &tmp );
	if ( ( tmp == 0xffffffff ) || ( tmp == 0 ) )
		return -ENODEV;


	pci->vendor = ( tmp & 0xffff );
	pci->device = ( tmp >> 16 );
	pci_read_config_dword ( pci, PCI_REVISION, &tmp );
	pci->class = ( tmp >> 8 );
	pci_read_config_byte ( pci, PCI_INTERRUPT_LINE, &pci->irq );
	pci_read_bases ( pci );


	snprintf ( pci->dev.name, sizeof ( pci->dev.name ),
		   "PCI%02x:%02x.%x", PCI_BUS ( pci->busdevfn ),
		   PCI_SLOT ( pci->busdevfn ), PCI_FUNC ( pci->busdevfn ) );
	pci->dev.desc.bus_type = BUS_TYPE_PCI;
	pci->dev.desc.location = pci->busdevfn;
	pci->dev.desc.vendor = pci->vendor;
	pci->dev.desc.device = pci->device;
	pci->dev.desc.class = pci->class;
	pci->dev.desc.ioaddr = pci->ioaddr;
	pci->dev.desc.irq = pci->irq;
	INIT_LIST_HEAD ( &pci->dev.siblings );
	INIT_LIST_HEAD ( &pci->dev.children );

	return 0;
}
