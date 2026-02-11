mpt_is_discovery_complete(MPT_ADAPTER *ioc)
{
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasIOUnitPage0_t *buffer;
	dma_addr_t dma_handle;
	int rc = 0;

	memset(&hdr, 0, sizeof(ConfigExtendedPageHeader_t));
	memset(&cfg, 0, sizeof(CONFIGPARMS));
	hdr.PageVersion = MPI_SASIOUNITPAGE0_PAGEVERSION;
	hdr.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	hdr.ExtPageType = MPI_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;
	cfg.cfghdr.ehdr = &hdr;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;

	if ((mpt_config(ioc, &cfg)))
		goto out;
	if (!hdr.ExtPageLength)
		goto out;

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
	    &dma_handle);
	if (!buffer)
		goto out;

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	if ((mpt_config(ioc, &cfg)))
		goto out_free_consistent;

	if (!(buffer->PhyData[0].PortFlags &
	    MPI_SAS_IOUNIT0_PORT_FLAGS_DISCOVERY_IN_PROGRESS))
		rc = 1;

 out_free_consistent:
	pci_free_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
	    buffer, dma_handle);
 out:
	return rc;
}
