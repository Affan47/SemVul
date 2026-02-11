efipci_read ( struct pci_device *pci, unsigned long location,
		  void *value ) {
	EFI_STATUS efirc;
	int rc;

	if ( ( efirc = efipci->Pci.Read ( efipci, EFIPCI_WIDTH ( location ),
					  efipci_address ( pci, location ), 1,
					  value ) ) != 0 ) {
		rc = -EEFI ( efirc );
		DBG ( "EFIPCI config read from " PCI_FMT " offset %02lx "
		      "failed: %s\n", PCI_ARGS ( pci ),
		      EFIPCI_OFFSET ( location ), strerror ( rc ) );
		return -EIO;
	}

	return 0;
}
