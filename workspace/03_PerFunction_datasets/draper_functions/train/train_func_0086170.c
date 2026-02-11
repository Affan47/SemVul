pci_vpd_read_dword ( struct pci_vpd *vpd, int address,
				uint32_t *data ) {
	struct pci_device *pci = vpd->pci;
	unsigned int cap = vpd->cap;
	unsigned int retries;
	uint16_t flag;


	if ( ! cap )
		return -ENOTTY;


	if ( pci_vpd_cache_is_valid ( vpd ) &&
	     ( vpd->cache.address == address ) ) {
		*data = vpd->cache.data;
		return 0;
	}


	pci_write_config_word ( pci, ( cap + PCI_VPD_ADDRESS ), address );


	for ( retries = 0 ; retries < PCI_VPD_MAX_WAIT_MS ; retries++ ) {


		pci_read_config_word ( pci, ( cap + PCI_VPD_ADDRESS ), &flag );
		if ( flag & PCI_VPD_FLAG ) {


			pci_read_config_dword ( pci, ( cap + PCI_VPD_DATA ),
						data );
			DBGC2 ( vpd, PCI_FMT " VPD %04x => %08x\n",
				PCI_ARGS ( pci ), address, htonl ( *data ) );


			vpd->cache.address = address;
			vpd->cache.data = *data;

			return 0;
		}


		mdelay ( 1 );
	}

	DBGC ( vpd, PCI_FMT " VPD %04x read via %02x timed out\n",
	       PCI_ARGS ( pci ), address, cap );
	return -ETIMEDOUT;
}
