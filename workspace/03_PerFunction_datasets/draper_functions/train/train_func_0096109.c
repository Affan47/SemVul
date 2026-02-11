qla4xxx_get_new_srb(struct scsi_qla_host *ha,
				       struct ddb_entry *ddb_entry,
				       struct scsi_cmnd *cmd)
{
	struct srb *srb;

	srb = mempool_alloc(ha->srb_mempool, GFP_ATOMIC);
	if (!srb)
		return srb;

	kref_init(&srb->srb_ref);
	srb->ha = ha;
	srb->ddb = ddb_entry;
	srb->cmd = cmd;
	srb->flags = 0;
	CMD_SP(cmd) = (void *)srb;

	return srb;
}
