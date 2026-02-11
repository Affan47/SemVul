_scsih_sas_device_status_change_event(struct MPT3SAS_ADAPTER *ioc,
	struct fw_event_work *fw_event)
{
	struct MPT3SAS_TARGET *target_priv_data;
	struct _sas_device *sas_device;
	u64 sas_address;
	unsigned long flags;
	Mpi2EventDataSasDeviceStatusChange_t *event_data =
		(Mpi2EventDataSasDeviceStatusChange_t *)
		fw_event->event_data;

	if (ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK)
		_scsih_sas_device_status_change_event_debug(ioc,
		     event_data);


	if ((ioc->facts.HeaderVersion >> 8) < 0xC)
		return;

	if (event_data->ReasonCode !=
	    MPI2_EVENT_SAS_DEV_STAT_RC_INTERNAL_DEVICE_RESET &&
	   event_data->ReasonCode !=
	    MPI2_EVENT_SAS_DEV_STAT_RC_CMP_INTERNAL_DEV_RESET)
		return;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_address = le64_to_cpu(event_data->SASAddress);
	sas_device = __mpt3sas_get_sdev_by_addr(ioc,
	    sas_address);

	if (!sas_device || !sas_device->starget)
		goto out;

	target_priv_data = sas_device->starget->hostdata;
	if (!target_priv_data)
		goto out;

	if (event_data->ReasonCode ==
	    MPI2_EVENT_SAS_DEV_STAT_RC_INTERNAL_DEVICE_RESET)
		target_priv_data->tm_busy = 1;
	else
		target_priv_data->tm_busy = 0;

out:
	if (sas_device)
		sas_device_put(sas_device);

	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

}
