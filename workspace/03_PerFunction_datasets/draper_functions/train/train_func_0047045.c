mpt3sas_config_set_manufacturing_pg11(struct MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply,
	struct Mpi2ManufacturingPage11_t *config_page)
{
	Mpi2ConfigRequest_t mpi_request;
	int r;

	memset(&mpi_request, 0, sizeof(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_MANUFACTURING;
	mpi_request.Header.PageNumber = 11;
	mpi_request.Header.PageVersion = MPI2_MANUFACTURING0_PAGEVERSION;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, NULL, 0);
	if (r)
		goto out;

	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    sizeof(*config_page));
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_WRITE_NVRAM;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	return r;
}
