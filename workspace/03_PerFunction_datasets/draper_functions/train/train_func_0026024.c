pvscsi_queue_lck(struct scsi_cmnd *cmd, void (*done)(struct scsi_cmnd *))
{
	struct Scsi_Host *host = cmd->device->host;
	struct pvscsi_adapter *adapter = shost_priv(host);
	struct pvscsi_ctx *ctx;
	unsigned long flags;

	spin_lock_irqsave(&adapter->hw_lock, flags);

	ctx = pvscsi_acquire_context(adapter, cmd);
	if (!ctx || pvscsi_queue_ring(adapter, ctx, cmd) != 0) {
		if (ctx)
			pvscsi_release_context(adapter, ctx);
		spin_unlock_irqrestore(&adapter->hw_lock, flags);
		return SCSI_MLQUEUE_HOST_BUSY;
	}

	cmd->scsi_done = done;

	dev_dbg(&cmd->device->sdev_gendev,
		"queued cmd %p, ctx %p, op=%x\n", cmd, ctx, cmd->cmnd[0]);

	spin_unlock_irqrestore(&adapter->hw_lock, flags);

	pvscsi_kick_io(adapter, cmd->cmnd[0]);

	return 0;
}
