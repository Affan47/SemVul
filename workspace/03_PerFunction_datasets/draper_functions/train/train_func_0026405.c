_scsih_search_responding_sas_devices(struct MPT3SAS_ADAPTER *ioc)
{
	Mpi2SasDevicePage0_t sas_device_pg0;
	Mpi2ConfigReply_t mpi_reply;
	u16 ioc_status;
	u16 handle;
	u32 device_info;

	pr_info(MPT3SAS_FMT "search for end-devices: start\n", ioc->name);

	if (list_empty(&ioc->sas_device_list))
		goto out;

	handle = 0xFFFF;
	while (!(mpt3sas_config_get_sas_device_pg0(ioc, &mpi_reply,
	    &sas_device_pg0, MPI2_SAS_DEVICE_PGAD_FORM_GET_NEXT_HANDLE,
	    handle))) {
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status != MPI2_IOCSTATUS_SUCCESS)
			break;
		handle = sas_device_pg0.DevHandle =
				le16_to_cpu(sas_device_pg0.DevHandle);
		device_info = le32_to_cpu(sas_device_pg0.DeviceInfo);
		if (!(_scsih_is_end_device(device_info)))
			continue;
		sas_device_pg0.SASAddress =
				le64_to_cpu(sas_device_pg0.SASAddress);
		sas_device_pg0.Slot = le16_to_cpu(sas_device_pg0.Slot);
		_scsih_mark_responding_sas_device(ioc, &sas_device_pg0);
	}

 out:
	pr_info(MPT3SAS_FMT "search for end-devices: complete\n",
	    ioc->name);
}
