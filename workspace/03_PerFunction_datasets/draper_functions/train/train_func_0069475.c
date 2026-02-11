_scsih_search_responding_expanders(struct MPT3SAS_ADAPTER *ioc)
{
	Mpi2ExpanderPage0_t expander_pg0;
	Mpi2ConfigReply_t mpi_reply;
	u16 ioc_status;
	u64 sas_address;
	u16 handle;

	pr_info(MPT3SAS_FMT "search for expanders: start\n", ioc->name);

	if (list_empty(&ioc->sas_expander_list))
		goto out;

	handle = 0xFFFF;
	while (!(mpt3sas_config_get_expander_pg0(ioc, &mpi_reply, &expander_pg0,
	    MPI2_SAS_EXPAND_PGAD_FORM_GET_NEXT_HNDL, handle))) {

		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status != MPI2_IOCSTATUS_SUCCESS)
			break;

		handle = le16_to_cpu(expander_pg0.DevHandle);
		sas_address = le64_to_cpu(expander_pg0.SASAddress);
		pr_info("\texpander present: handle(0x%04x), sas_addr(0x%016llx)\n",
			handle,
		    (unsigned long long)sas_address);
		_scsih_mark_responding_expander(ioc, sas_address, handle);
	}

 out:
	pr_info(MPT3SAS_FMT "search for expanders: complete\n", ioc->name);
}
