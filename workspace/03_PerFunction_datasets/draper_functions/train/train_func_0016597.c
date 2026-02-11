mpt3sas_ctl_reset_handler(struct MPT3SAS_ADAPTER *ioc, int reset_phase)
{
	int i;
	u8 issue_reset;

	switch (reset_phase) {
	case MPT3_IOC_PRE_RESET:
		dtmprintk(ioc, pr_info(MPT3SAS_FMT
			"%s: MPT3_IOC_PRE_RESET\n", ioc->name, __func__));
		for (i = 0; i < MPI2_DIAG_BUF_TYPE_COUNT; i++) {
			if (!(ioc->diag_buffer_status[i] &
			    MPT3_DIAG_BUFFER_IS_REGISTERED))
				continue;
			if ((ioc->diag_buffer_status[i] &
			    MPT3_DIAG_BUFFER_IS_RELEASED))
				continue;
			mpt3sas_send_diag_release(ioc, i, &issue_reset);
		}
		break;
	case MPT3_IOC_AFTER_RESET:
		dtmprintk(ioc, pr_info(MPT3SAS_FMT
			"%s: MPT3_IOC_AFTER_RESET\n", ioc->name, __func__));
		if (ioc->ctl_cmds.status & MPT3_CMD_PENDING) {
			ioc->ctl_cmds.status |= MPT3_CMD_RESET;
			mpt3sas_base_free_smid(ioc, ioc->ctl_cmds.smid);
			complete(&ioc->ctl_cmds.done);
		}
		break;
	case MPT3_IOC_DONE_RESET:
		dtmprintk(ioc, pr_info(MPT3SAS_FMT
			"%s: MPT3_IOC_DONE_RESET\n", ioc->name, __func__));

		for (i = 0; i < MPI2_DIAG_BUF_TYPE_COUNT; i++) {
			if (!(ioc->diag_buffer_status[i] &
			    MPT3_DIAG_BUFFER_IS_REGISTERED))
				continue;
			if ((ioc->diag_buffer_status[i] &
			    MPT3_DIAG_BUFFER_IS_RELEASED))
				continue;
			ioc->diag_buffer_status[i] |=
			    MPT3_DIAG_BUFFER_IS_DIAG_RESET;
		}
		break;
	}
}
