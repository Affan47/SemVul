scsih_target_reset(struct scsi_cmnd *scmd)
{
	struct MPT3SAS_ADAPTER *ioc = shost_priv(scmd->device->host);
	struct MPT3SAS_DEVICE *sas_device_priv_data;
	struct _sas_device *sas_device = NULL;
	u16	handle;
	int r;
	struct scsi_target *starget = scmd->device->sdev_target;
	struct MPT3SAS_TARGET *target_priv_data = starget->hostdata;

	starget_printk(KERN_INFO, starget, "attempting target reset! scmd(%p)\n",
		scmd);
	_scsih_tm_display_info(ioc, scmd);

	sas_device_priv_data = scmd->device->hostdata;
	if (!sas_device_priv_data || !sas_device_priv_data->sas_target) {
		starget_printk(KERN_INFO, starget, "target been deleted! scmd(%p)\n",
			scmd);
		scmd->result = DID_NO_CONNECT << 16;
		scmd->scsi_done(scmd);
		r = SUCCESS;
		goto out;
	}


	handle = 0;
	if (sas_device_priv_data->sas_target->flags &
	    MPT_TARGET_FLAGS_RAID_COMPONENT) {
		sas_device = mpt3sas_get_sdev_from_target(ioc,
				target_priv_data);
		if (sas_device)
			handle = sas_device->volume_handle;
	} else
		handle = sas_device_priv_data->sas_target->handle;

	if (!handle) {
		scmd->result = DID_RESET << 16;
		r = FAILED;
		goto out;
	}

	r = mpt3sas_scsih_issue_tm(ioc, handle, scmd->device->channel,
	    scmd->device->id, 0, MPI2_SCSITASKMGMT_TASKTYPE_TARGET_RESET, 0,
	    30, TM_MUTEX_ON);

 out:
	starget_printk(KERN_INFO, starget, "target reset: %s scmd(%p)\n",
	    ((r == SUCCESS) ? "SUCCESS" : "FAILED"), scmd);

	if (sas_device)
		sas_device_put(sas_device);

	return r;
}
