scsi_eh_get_sense(struct list_head *work_q,
		      struct list_head *done_q)
{
	struct scsi_cmnd *scmd, *next;
	struct Scsi_Host *shost;
	int rtn;


	list_for_each_entry_safe(scmd, next, work_q, eh_entry) {
		if ((scmd->eh_eflags & SCSI_EH_CANCEL_CMD) ||
		    (scmd->eh_eflags & SCSI_EH_ABORT_SCHEDULED) ||
		    SCSI_SENSE_VALID(scmd))
			continue;

		shost = scmd->device->host;
		if (scsi_host_eh_past_deadline(shost)) {
			SCSI_LOG_ERROR_RECOVERY(3,
				scmd_printk(KERN_INFO, scmd,
					    "%s: skip request sense, past eh deadline\n",
					     current->comm));
			break;
		}
		if (status_byte(scmd->result) != CHECK_CONDITION)


			continue;

		SCSI_LOG_ERROR_RECOVERY(2, scmd_printk(KERN_INFO, scmd,
						  "%s: requesting sense\n",
						  current->comm));
		rtn = scsi_request_sense(scmd);
		if (rtn != SUCCESS)
			continue;

		SCSI_LOG_ERROR_RECOVERY(3, scmd_printk(KERN_INFO, scmd,
			"sense requested, result %x\n", scmd->result));
		SCSI_LOG_ERROR_RECOVERY(3, scsi_print_sense(scmd));

		rtn = scsi_decide_disposition(scmd);


		if (rtn == SUCCESS)


			scmd->retries = scmd->allowed;
		else if (rtn != NEEDS_RETRY)
			continue;

		scsi_eh_finish_cmd(scmd, done_q);
	}

	return list_empty(work_q);
}
