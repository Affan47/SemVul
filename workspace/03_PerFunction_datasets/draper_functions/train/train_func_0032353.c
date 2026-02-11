scmd_eh_abort_handler(struct work_struct *work)
{
	struct scsi_cmnd *scmd =
		container_of(work, struct scsi_cmnd, abort_work.work);
	struct scsi_device *sdev = scmd->device;
	int rtn;

	if (scsi_host_eh_past_deadline(sdev->host)) {
		SCSI_LOG_ERROR_RECOVERY(3,
			scmd_printk(KERN_INFO, scmd,
				    "eh timeout, not aborting\n"));
	} else {
		SCSI_LOG_ERROR_RECOVERY(3,
			scmd_printk(KERN_INFO, scmd,
				    "aborting command\n"));
		rtn = scsi_try_to_abort_cmd(sdev->host->hostt, scmd);
		if (rtn == SUCCESS) {
			set_host_byte(scmd, DID_TIME_OUT);
			if (scsi_host_eh_past_deadline(sdev->host)) {
				SCSI_LOG_ERROR_RECOVERY(3,
					scmd_printk(KERN_INFO, scmd,
						    "eh timeout, not retrying "
						    "aborted command\n"));
			} else if (!scsi_noretry_cmd(scmd) &&
			    (++scmd->retries <= scmd->allowed)) {
				SCSI_LOG_ERROR_RECOVERY(3,
					scmd_printk(KERN_WARNING, scmd,
						    "retry aborted command\n"));
				scsi_queue_insert(scmd, SCSI_MLQUEUE_EH_RETRY);
				return;
			} else {
				SCSI_LOG_ERROR_RECOVERY(3,
					scmd_printk(KERN_WARNING, scmd,
						    "finish aborted command\n"));
				scsi_finish_command(scmd);
				return;
			}
		} else {
			SCSI_LOG_ERROR_RECOVERY(3,
				scmd_printk(KERN_INFO, scmd,
					    "cmd abort %s\n",
					    (rtn == FAST_IO_FAIL) ?
					    "not send" : "failed"));
		}
	}

	if (!scsi_eh_scmd_add(scmd, 0)) {
		SCSI_LOG_ERROR_RECOVERY(3,
			scmd_printk(KERN_WARNING, scmd,
				    "terminate aborted command\n"));
		set_host_byte(scmd, DID_TIME_OUT);
		scsi_finish_command(scmd);
	}
}
