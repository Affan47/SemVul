bofm_test ( struct pci_device *pci ) {
	int bofmrc;

	printf ( "BOFMTEST using " PCI_FMT "\n", PCI_ARGS ( pci ) );


	printf ( "BOFMTEST performing harvest\n" );
	bofmtab_harvest.en.busdevfn = pci->busdevfn;
	DBG_HDA ( 0, &bofmtab_harvest, sizeof ( bofmtab_harvest ) );
	bofmrc = bofm ( virt_to_user ( &bofmtab_harvest ), pci );
	printf ( "BOFMTEST harvest result %08x\n", bofmrc );
	if ( bofmtab_harvest.en.options & BOFM_EN_HVST ) {
		printf ( "BOFMTEST harvested MAC address %s\n",
			 eth_ntoa ( &bofmtab_harvest.en.mac_a ) );
	} else {
		printf ( "BOFMTEST failed to harvest a MAC address\n" );
	}
	DBG_HDA ( 0, &bofmtab_harvest, sizeof ( bofmtab_harvest ) );


	printf ( "BOFMTEST performing update\n" );
	bofmtab_update.en.busdevfn = pci->busdevfn;
	DBG_HDA ( 0, &bofmtab_update, sizeof ( bofmtab_update ) );
	bofmrc = bofm ( virt_to_user ( &bofmtab_update ), pci );
	printf ( "BOFMTEST update result %08x\n", bofmrc );
	if ( bofmtab_update.en.options & BOFM_EN_CSM_SUCCESS ) {
		printf ( "BOFMTEST updated MAC address to %s\n",
			 eth_ntoa ( &bofmtab_update.en.mac_a ) );
	} else {
		printf ( "BOFMTEST failed to update MAC address\n" );
	}
	DBG_HDA ( 0, &bofmtab_update, sizeof ( bofmtab_update ) );
}
