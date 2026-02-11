nvs_vpd_read ( struct nvs_device *nvs, unsigned int field,
			  void *data, size_t len ) {
	struct nvs_vpd_device *nvsvpd =
		container_of ( nvs, struct nvs_vpd_device, nvs );
	struct pci_device *pci = nvsvpd->vpd.pci;
	unsigned int address;
	size_t max_len;
	int rc;


	if ( len == 0 )
		return 0;


	if ( ( rc = pci_vpd_find ( &nvsvpd->vpd, field, &address,
				   &max_len ) ) != 0 ) {
		DBGC ( pci, PCI_FMT " NVS VPD could not locate field "
		       PCI_VPD_FIELD_FMT ": %s\n", PCI_ARGS ( pci ),
		       PCI_VPD_FIELD_ARGS ( field ), strerror ( rc ) );
		return rc;
	}


	if ( len > max_len ) {
		DBGC ( pci, PCI_FMT " NVS VPD cannot read %#02zx bytes "
		       "beyond field " PCI_VPD_FIELD_FMT " at [%04x,%04zx)\n",
		       PCI_ARGS ( pci ), len, PCI_VPD_FIELD_ARGS ( field ),
		       address, ( address + max_len ) );
		return -ENXIO;
	}


	if ( ( rc = pci_vpd_read ( &nvsvpd->vpd, address, data, len ) ) != 0 ) {
		DBGC ( pci, PCI_FMT " NVS VPD could not read field "
		       PCI_VPD_FIELD_FMT " at [%04x,%04zx): %s\n",
		       PCI_ARGS ( pci ), PCI_VPD_FIELD_ARGS ( field ),
		       address, ( address + len ), strerror ( rc ) );
		return rc;
	}

	return 0;
}
