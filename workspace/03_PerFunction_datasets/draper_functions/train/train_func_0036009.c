sym_xpt_done(struct sym_hcb *np, struct scsi_cmnd *cmd)
{
	struct sym_ucmd *ucmd = SYM_UCMD_PTR(cmd);
	BUILD_BUG_ON(sizeof(struct scsi_pointer) < sizeof(struct sym_ucmd));

	if (ucmd->eh_done)
		complete(ucmd->eh_done);

	scsi_dma_unmap(cmd);
	cmd->scsi_done(cmd);
}
