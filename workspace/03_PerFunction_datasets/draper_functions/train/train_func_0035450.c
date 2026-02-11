hpsa_scsi_queue_command(struct Scsi_Host *sh, struct scsi_cmnd *cmd)
{
	struct ctlr_info *h;
	struct hpsa_scsi_dev_t *dev;
	unsigned char scsi3addr[8];
	struct CommandList *c;
	int rc = 0;


	h = sdev_to_hba(cmd->device);

	BUG_ON(cmd->request->tag < 0);

	dev = cmd->device->hostdata;
	if (!dev) {
		cmd->result = DID_NO_CONNECT << 16;
		cmd->scsi_done(cmd);
		return 0;
	}

	memcpy(scsi3addr, dev->scsi3addr, sizeof(scsi3addr));

	if (unlikely(lockup_detected(h))) {
		cmd->result = DID_NO_CONNECT << 16;
		cmd->scsi_done(cmd);
		return 0;
	}
	c = cmd_tagged_alloc(h, cmd);


	if (likely(cmd->retries == 0 &&
		cmd->request->cmd_type == REQ_TYPE_FS &&
		h->acciopath_status)) {
		rc = hpsa_ioaccel_submit(h, c, cmd, scsi3addr);
		if (rc == 0)
			return 0;
		if (rc == SCSI_MLQUEUE_HOST_BUSY) {
			hpsa_cmd_resolve_and_free(h, c);
			return SCSI_MLQUEUE_HOST_BUSY;
		}
	}
	return hpsa_ciss_submit(h, c, cmd, scsi3addr);
}
