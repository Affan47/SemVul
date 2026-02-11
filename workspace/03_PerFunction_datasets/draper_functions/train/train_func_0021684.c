pcibus_probe ( struct root_device *rootdev ) {
	struct pci_device *pci = NULL;
	unsigned int max_bus;
	unsigned int bus;
	unsigned int devfn;
	uint8_t hdrtype = 0;
	uint32_t tmp;
	int rc;

	max_bus = pci_max_bus();
	for ( bus = 0 ; bus <= max_bus ; bus++ ) {
		for ( devfn = 0 ; devfn <= 0xff ; devfn++ ) {


			if ( ! pci )
				pci = malloc ( sizeof ( *pci ) );
			if ( ! pci ) {
				rc = -ENOMEM;
				goto err;
			}
			memset ( pci, 0, sizeof ( *pci ) );
			pci->bus = bus;
			pci->devfn = devfn;


			if ( PCI_FUNC ( devfn ) == 0 ) {
				pci_read_config_byte ( pci, PCI_HEADER_TYPE,
						       &hdrtype );
			} else if ( ! ( hdrtype & 0x80 ) ) {
					continue;
			}


			pci_read_config_dword ( pci, PCI_VENDOR_ID, &tmp );
			if ( ( tmp == 0xffffffff ) || ( tmp == 0 ) )
				continue;


			pci->vendor = ( tmp & 0xffff );
			pci->device = ( tmp >> 16 );
			pci_read_config_dword ( pci, PCI_REVISION, &tmp );
			pci->class = ( tmp >> 8 );
			pci_read_config_byte ( pci, PCI_INTERRUPT_LINE,
					       &pci->irq );
			pci_read_bases ( pci );


			snprintf ( pci->dev.name, sizeof ( pci->dev.name ),
				   "PCI%02x:%02x.%x", bus,
				   PCI_SLOT ( devfn ), PCI_FUNC ( devfn ) );
			pci->dev.desc.bus_type = BUS_TYPE_PCI;
			pci->dev.desc.location = PCI_BUSDEVFN (bus, devfn);
			pci->dev.desc.vendor = pci->vendor;
			pci->dev.desc.device = pci->device;
			pci->dev.desc.class = pci->class;
			pci->dev.desc.ioaddr = pci->ioaddr;
			pci->dev.desc.irq = pci->irq;
			pci->dev.parent = &rootdev->dev;
			list_add ( &pci->dev.siblings, &rootdev->dev.children);
			INIT_LIST_HEAD ( &pci->dev.children );


			if ( pci_probe ( pci ) == 0 ) {

				pci = NULL;
			} else {

				list_del ( &pci->dev.siblings );
			}
		}
	}

	free ( pci );
	return 0;

 err:
	free ( pci );
	pcibus_remove ( rootdev );
	return rc;
}
