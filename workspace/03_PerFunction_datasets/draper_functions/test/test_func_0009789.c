mpt3sas_send_diag_release(struct MPT3SAS_ADAPTER *ioc, u8 buffer_type,
	u8 *issue_reset)
{
	Mpi2DiagReleaseRequest_t *mpi_request;
	Mpi2DiagReleaseReply_t *mpi_reply;
	u16 smid;
	u16 ioc_status;
	u32 ioc_state;
	int rc;
	unsigned long timeleft;

	dctlprintk(ioc, pr_info(MPT3SAS_FMT "%s\n", ioc->name,
	    __func__));

	rc = 0;
	*issue_reset = 0;

	ioc_state = mpt3sas_base_get_iocstate(ioc, 1);
	if (ioc_state != MPI2_IOC_STATE_OPERATIONAL) {
		if (ioc->diag_buffer_status[buffer_type] &
		    MPT3_DIAG_BUFFER_IS_REGISTERED)
			ioc->diag_buffer_status[buffer_type] |=
			    MPT3_DIAG_BUFFER_IS_RELEASED;
		dctlprintk(ioc, pr_info(MPT3SAS_FMT
			"%s: skipping due to FAULT state\n", ioc->name,
		    __func__));
		rc = -EAGAIN;
		goto out;
	}

	if (ioc->ctl_cmds.status != MPT3_CMD_NOT_USED) {
		pr_err(MPT3SAS_FMT "%s: ctl_cmd in use\n",
		    ioc->name, __func__);
		rc = -EAGAIN;
		goto out;
	}

	smid = mpt3sas_base_get_smid(ioc, ioc->ctl_cb_idx);
	if (!smid) {
		pr_err(MPT3SAS_FMT "%s: failed obtaining a smid\n",
		    ioc->name, __func__);
		rc = -EAGAIN;
		goto out;
	}

	ioc->ctl_cmds.status = MPT3_CMD_PENDING;
	memset(ioc->ctl_cmds.reply, 0, ioc->reply_sz);
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->ctl_cmds.smid = smid;

	mpi_request->Function = MPI2_FUNCTION_DIAG_RELEASE;
	mpi_request->BufferType = buffer_type;
	mpi_request->VF_ID = 0;
	mpi_request->VP_ID = 0;

	init_completion(&ioc->ctl_cmds.done);
	mpt3sas_base_put_smid_default(ioc, smid);
	timeleft = wait_for_completion_timeout(&ioc->ctl_cmds.done,
	    MPT3_IOCTL_DEFAULT_TIMEOUT*HZ);

	if (!(ioc->ctl_cmds.status & MPT3_CMD_COMPLETE)) {
		pr_err(MPT3SAS_FMT "%s: timeout\n", ioc->name,
		    __func__);
		_debug_dump_mf(mpi_request,
		    sizeof(Mpi2DiagReleaseRequest_t)/4);
		if (!(ioc->ctl_cmds.status & MPT3_CMD_RESET))
			*issue_reset = 1;
		rc = -EFAULT;
		goto out;
	}


	if ((ioc->ctl_cmds.status & MPT3_CMD_REPLY_VALID) == 0) {
		pr_err(MPT3SAS_FMT "%s: no reply message\n",
		    ioc->name, __func__);
		rc = -EFAULT;
		goto out;
	}

	mpi_reply = ioc->ctl_cmds.reply;
	ioc_status = le16_to_cpu(mpi_reply->IOCStatus) & MPI2_IOCSTATUS_MASK;

	if (ioc_status == MPI2_IOCSTATUS_SUCCESS) {
		ioc->diag_buffer_status[buffer_type] |=
		    MPT3_DIAG_BUFFER_IS_RELEASED;
		dctlprintk(ioc, pr_info(MPT3SAS_FMT "%s: success\n",
		    ioc->name, __func__));
	} else {
		pr_info(MPT3SAS_FMT
			"%s: ioc_status(0x%04x) log_info(0x%08x)\n",
			ioc->name, __func__,
		    ioc_status, le32_to_cpu(mpi_reply->IOCLogInfo));
		rc = -EFAULT;
	}

 out:
	ioc->ctl_cmds.status = MPT3_CMD_NOT_USED;
	return rc;
}
