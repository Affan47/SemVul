lpfc_update_stats(struct lpfc_hba *phba, struct  lpfc_scsi_buf *lpfc_cmd)
{
	struct lpfc_rport_data *rdata = lpfc_cmd->rdata;
	struct lpfc_nodelist *pnode = rdata->pnode;
	struct scsi_cmnd *cmd = lpfc_cmd->pCmd;
	unsigned long flags;
	struct Scsi_Host  *shost = cmd->device->host;
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	unsigned long latency;
	int i;

	if (cmd->result)
		return;

	latency = jiffies_to_msecs((long)jiffies - (long)lpfc_cmd->start_time);

	spin_lock_irqsave(shost->host_lock, flags);
	if (!vport->stat_data_enabled ||
		vport->stat_data_blocked ||
		!pnode ||
		!pnode->lat_data ||
		(phba->bucket_type == LPFC_NO_BUCKET)) {
		spin_unlock_irqrestore(shost->host_lock, flags);
		return;
	}

	if (phba->bucket_type == LPFC_LINEAR_BUCKET) {
		i = (latency + phba->bucket_step - 1 - phba->bucket_base)/
			phba->bucket_step;

		if (i < 0)
			i = 0;
		else if (i >= LPFC_MAX_BUCKET_COUNT)
			i = LPFC_MAX_BUCKET_COUNT - 1;
	} else {
		for (i = 0; i < LPFC_MAX_BUCKET_COUNT-1; i++)
			if (latency <= (phba->bucket_base +
				((1<<i)*phba->bucket_step)))
				break;
	}

	pnode->lat_data[i].cmd_count++;
	spin_unlock_irqrestore(shost->host_lock, flags);
}
