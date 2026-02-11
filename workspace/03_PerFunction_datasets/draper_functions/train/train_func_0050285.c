i91u_queuecommand_lck(struct scsi_cmnd *cmd,
		void (*done)(struct scsi_cmnd *))
{
	struct initio_host *host = (struct initio_host *) cmd->device->host->hostdata;
	struct scsi_ctrl_blk *cmnd;

	cmd->scsi_done = done;

	cmnd = initio_alloc_scb(host);
	if (!cmnd)
		return SCSI_MLQUEUE_HOST_BUSY;

	initio_build_scb(host, cmnd, cmd);
	initio_exec_scb(host, cmnd);
	return 0;
}
