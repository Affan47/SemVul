_scsih_turn_on_pfa_led(struct MPT3SAS_ADAPTER *ioc, u16 handle)
{
	Mpi2SepReply_t mpi_reply;
	Mpi2SepRequest_t mpi_request;
	struct _sas_device *sas_device;

	sas_device = mpt3sas_get_sdev_by_handle(ioc, handle);
	if (!sas_device)
		return;

	memset(&mpi_request, 0, sizeof(Mpi2SepRequest_t));
	mpi_request.Function = MPI2_FUNCTION_SCSI_ENCLOSURE_PROCESSOR;
	mpi_request.Action = MPI2_SEP_REQ_ACTION_WRITE_STATUS;
	mpi_request.SlotStatus =
	    cpu_to_le32(MPI2_SEP_REQ_SLOTSTATUS_PREDICTED_FAULT);
	mpi_request.DevHandle = cpu_to_le16(handle);
	mpi_request.Flags = MPI2_SEP_REQ_FLAGS_DEVHANDLE_ADDRESS;
	if ((mpt3sas_base_scsi_enclosure_processor(ioc, &mpi_reply,
	    &mpi_request)) != 0) {
		pr_err(MPT3SAS_FMT "failure at %s:%d/%s()!\n", ioc->name,
		__FILE__, __LINE__, __func__);
		goto out;
	}
	sas_device->pfa_led_on = 1;

	if (mpi_reply.IOCStatus || mpi_reply.IOCLogInfo) {
		dewtprintk(ioc, pr_info(MPT3SAS_FMT
			"enclosure_processor: ioc_status (0x%04x), loginfo(0x%08x)\n",
			ioc->name, le16_to_cpu(mpi_reply.IOCStatus),
		    le32_to_cpu(mpi_reply.IOCLogInfo)));
		goto out;
	}
out:
	sas_device_put(sas_device);
}
