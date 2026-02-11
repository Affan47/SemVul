mvumi_timed_out(struct scsi_cmnd *scmd)
{
	struct mvumi_cmd *cmd = (struct mvumi_cmd *) scmd->SCp.ptr;
	struct Scsi_Host *host = scmd->device->host;
	struct mvumi_hba *mhba = shost_priv(host);
	unsigned long flags;

	spin_lock_irqsave(mhba->shost->host_lock, flags);

	if (mhba->tag_cmd[cmd->frame->tag]) {
		mhba->tag_cmd[cmd->frame->tag] = 0;
		tag_release_one(mhba, &mhba->tag_pool, cmd->frame->tag);
	}
	if (!list_empty(&cmd->queue_pointer))
		list_del_init(&cmd->queue_pointer);
	else
		atomic_dec(&mhba->fw_outstanding);

	scmd->result = (DRIVER_INVALID << 24) | (DID_ABORT << 16);
	scmd->SCp.ptr = NULL;
	if (scsi_bufflen(scmd)) {
		if (scsi_sg_count(scmd)) {
			pci_unmap_sg(mhba->pdev,
				scsi_sglist(scmd),
				scsi_sg_count(scmd),
				(int)scmd->sc_data_direction);
		} else {
			pci_unmap_single(mhba->pdev,
				scmd->SCp.dma_handle,
				scsi_bufflen(scmd),
				(int)scmd->sc_data_direction);

			scmd->SCp.dma_handle = 0;
		}
	}
	mvumi_return_cmd(mhba, cmd);
	spin_unlock_irqrestore(mhba->shost->host_lock, flags);

	return BLK_EH_NOT_HANDLED;
}
