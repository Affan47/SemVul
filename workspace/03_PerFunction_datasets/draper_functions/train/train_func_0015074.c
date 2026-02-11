mptsas_sas_phy_pg0(MPT_ADAPTER *ioc, struct mptsas_phyinfo *phy_info,
		u32 form, u32 form_specific)
{
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasPhyPage0_t *buffer;
	dma_addr_t dma_handle;
	int error;

	hdr.PageVersion = MPI_SASPHY0_PAGEVERSION;
	hdr.ExtPageLength = 0;
	hdr.PageNumber = 0;
	hdr.Reserved1 = 0;
	hdr.Reserved2 = 0;
	hdr.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	hdr.ExtPageType = MPI_CONFIG_EXTPAGETYPE_SAS_PHY;

	cfg.cfghdr.ehdr = &hdr;
	cfg.dir = 0;
	cfg.timeout = SAS_CONFIG_PAGE_TIMEOUT;


	cfg.physAddr = -1;
	cfg.pageAddr = form + form_specific;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;

	error = mpt_config(ioc, &cfg);
	if (error)
		goto out;

	if (!hdr.ExtPageLength) {
		error = -ENXIO;
		goto out;
	}

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
				      &dma_handle);
	if (!buffer) {
		error = -ENOMEM;
		goto out;
	}

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	error = mpt_config(ioc, &cfg);
	if (error)
		goto out_free_consistent;

	mptsas_print_phy_pg0(ioc, buffer);

	phy_info->hw_link_rate = buffer->HwLinkRate;
	phy_info->programmed_link_rate = buffer->ProgrammedLinkRate;
	phy_info->identify.handle = le16_to_cpu(buffer->OwnerDevHandle);
	phy_info->attached.handle = le16_to_cpu(buffer->AttachedDevHandle);

 out_free_consistent:
	pci_free_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
			    buffer, dma_handle);
 out:
	return error;
}
