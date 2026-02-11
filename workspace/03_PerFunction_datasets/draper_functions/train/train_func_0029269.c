scsi_unjam_host(struct Scsi_Host *shost)
{
	unsigned long flags;
	LIST_HEAD(eh_work_q);
	LIST_HEAD(eh_done_q);

	spin_lock_irqsave(shost->host_lock, flags);
	list_splice_init(&shost->eh_cmd_q, &eh_work_q);
	spin_unlock_irqrestore(shost->host_lock, flags);

	SCSI_LOG_ERROR_RECOVERY(1, scsi_eh_prt_fail_stats(shost, &eh_work_q));

	if (!scsi_eh_get_sense(&eh_work_q, &eh_done_q))
		if (!scsi_eh_abort_cmds(&eh_work_q, &eh_done_q))
			scsi_eh_ready_devs(shost, &eh_work_q, &eh_done_q);

	spin_lock_irqsave(shost->host_lock, flags);
	if (shost->eh_deadline != -1)
		shost->last_reset = 0;
	spin_unlock_irqrestore(shost->host_lock, flags);
	scsi_eh_flush_done_q(&eh_done_q);
}
