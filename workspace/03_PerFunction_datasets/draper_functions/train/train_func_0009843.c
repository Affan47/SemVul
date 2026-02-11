mptfc_WriteFcPortPage1(MPT_ADAPTER *ioc, int portnum)
{
	ConfigPageHeader_t	 hdr;
	CONFIGPARMS		 cfg;
	int			 rc;

	if (portnum > 1)
		return -EINVAL;

	if (!(ioc->fc_data.fc_port_page1[portnum].data))
		return -EINVAL;


	hdr.PageVersion = 0;
	hdr.PageLength = 0;
	hdr.PageNumber = 1;
	hdr.PageType = MPI_CONFIG_PAGETYPE_FC_PORT;
	cfg.cfghdr.hdr = &hdr;
	cfg.physAddr = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	cfg.pageAddr = portnum;
	cfg.timeout = 0;

	if ((rc = mpt_config(ioc, &cfg)) != 0)
		return rc;

	if (hdr.PageLength == 0)
		return -ENODEV;

	if (hdr.PageLength*4 != ioc->fc_data.fc_port_page1[portnum].pg_sz)
		return -EINVAL;

	cfg.physAddr = ioc->fc_data.fc_port_page1[portnum].dma;
	cfg.action = MPI_CONFIG_ACTION_PAGE_WRITE_CURRENT;
	cfg.dir = 1;

	rc = mpt_config(ioc, &cfg);

	return rc;
}
