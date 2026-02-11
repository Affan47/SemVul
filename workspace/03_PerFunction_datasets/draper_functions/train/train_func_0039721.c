nvs_vpd_init ( struct nvs_vpd_device *nvsvpd, struct pci_device *pci ) {
	int rc;


	if ( ( rc = pci_vpd_init ( &nvsvpd->vpd, pci ) ) != 0 ) {
		DBGC ( pci, PCI_FMT " NVS could not initialise "
		       "VPD: %s\n", PCI_ARGS ( pci ), strerror ( rc ) );
		return rc;
	}


	nvsvpd->nvs.read = nvs_vpd_read;
	nvsvpd->nvs.write = nvs_vpd_write;

	return 0;
}
