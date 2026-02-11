_base_event_notification(struct MPT3SAS_ADAPTER *ioc, int sleep_flag)
{
	Mpi2EventNotificationRequest_t *mpi_request;
	unsigned long timeleft;
	u16 smid;
	int r = 0;
	int i;

	dinitprintk(ioc, pr_info(MPT3SAS_FMT "%s\n", ioc->name,
	    __func__));

	if (ioc->base_cmds.status & MPT3_CMD_PENDING) {
		pr_err(MPT3SAS_FMT "%s: internal command already in use\n",
		    ioc->name, __func__);
		return -EAGAIN;
	}

	smid = mpt3sas_base_get_smid(ioc, ioc->base_cb_idx);
	if (!smid) {
		pr_err(MPT3SAS_FMT "%s: failed obtaining a smid\n",
		    ioc->name, __func__);
		return -EAGAIN;
	}
	ioc->base_cmds.status = MPT3_CMD_PENDING;
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->base_cmds.smid = smid;
	memset(mpi_request, 0, sizeof(Mpi2EventNotificationRequest_t));
	mpi_request->Function = MPI2_FUNCTION_EVENT_NOTIFICATION;
	mpi_request->VF_ID = 0;
	mpi_request->VP_ID = 0;
	for (i = 0; i < MPI2_EVENT_NOTIFY_EVENTMASK_WORDS; i++)
		mpi_request->EventMasks[i] =
		    cpu_to_le32(ioc->event_masks[i]);
	init_completion(&ioc->base_cmds.done);
	mpt3sas_base_put_smid_default(ioc, smid);
	timeleft = wait_for_completion_timeout(&ioc->base_cmds.done, 30*HZ);
	if (!(ioc->base_cmds.status & MPT3_CMD_COMPLETE)) {
		pr_err(MPT3SAS_FMT "%s: timeout\n",
		    ioc->name, __func__);
		_debug_dump_mf(mpi_request,
		    sizeof(Mpi2EventNotificationRequest_t)/4);
		if (ioc->base_cmds.status & MPT3_CMD_RESET)
			r = -EFAULT;
		else
			r = -ETIME;
	} else
		dinitprintk(ioc, pr_info(MPT3SAS_FMT "%s: complete\n",
		    ioc->name, __func__));
	ioc->base_cmds.status = MPT3_CMD_NOT_USED;
	return r;
}
