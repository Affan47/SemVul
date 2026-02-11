pcibus_probe ( struct root_device *rootdev ) {
	struct pci_device *pci = NULL;
	int busdevfn = 0;
	int rc;

	for ( busdevfn = 0 ; 1 ; busdevfn++ ) {


		if ( ! pci )
			pci = malloc ( sizeof ( *pci ) );
		if ( ! pci ) {
			rc = -ENOMEM;
			goto err;
		}


		busdevfn = pci_find_next ( pci, busdevfn );
		if ( busdevfn < 0 )
			break;


		if ( ( rc = pci_find_driver ( pci ) ) != 0 ) {
			DBGC ( pci, PCI_FMT " (%04x:%04x) has no driver\n",
			       PCI_ARGS ( pci ), pci->vendor, pci->device );
			continue;
		}


		pci->dev.parent = &rootdev->dev;
		list_add ( &pci->dev.siblings, &rootdev->dev.children);


		if ( ( rc = pci_probe ( pci ) ) == 0 ) {

			pci = NULL;
		} else {

			list_del ( &pci->dev.siblings );
		}
	}

	free ( pci );
	return 0;

 err:
	free ( pci );
	pcibus_remove ( rootdev );
	return rc;
}
