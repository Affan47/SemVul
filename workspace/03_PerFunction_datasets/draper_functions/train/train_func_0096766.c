scsi_eh_abort_cmds(struct list_head *work_q,
			      struct list_head *done_q)
{
	struct scsi_cmnd *scmd, *next;
	LIST_HEAD(check_list);
	int rtn;
	struct Scsi_Host *shost;

	list_for_each_entry_safe(scmd, next, work_q, eh_entry) {
		if (!(scmd->eh_eflags & SCSI_EH_CANCEL_CMD))
			continue;
		shost = scmd->device->host;
		if (scsi_host_eh_past_deadline(shost)) {
			list_splice_init(&check_list, work_q);
			SCSI_LOG_ERROR_RECOVERY(3,
				scmd_printk(KERN_INFO, scmd,
					    "%s: skip aborting cmd, past eh deadline\n",
					    current->comm));
			return list_empty(work_q);
		}
		SCSI_LOG_ERROR_RECOVERY(3,
			scmd_printk(KERN_INFO, scmd,
				     "%s: aborting cmd\n", current->comm));
		rtn = scsi_try_to_abort_cmd(shost->hostt, scmd);
		if (rtn == FAILED) {
			SCSI_LOG_ERROR_RECOVERY(3,
				scmd_printk(KERN_INFO, scmd,
					    "%s: aborting cmd failed\n",
					     current->comm));
			list_splice_init(&check_list, work_q);
			return list_empty(work_q);
		}
		scmd->eh_eflags &= ~SCSI_EH_CANCEL_CMD;
		if (rtn == FAST_IO_FAIL)
			scsi_eh_finish_cmd(scmd, done_q);
		else
			list_move_tail(&scmd->eh_entry, &check_list);
	}

	return scsi_eh_test_devices(&check_list, work_q, done_q, 0);
}
