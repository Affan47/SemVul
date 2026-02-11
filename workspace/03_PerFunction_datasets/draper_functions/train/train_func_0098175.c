sas_scsi_timed_out(struct scsi_cmnd *cmd)
{
	scmd_dbg(cmd, "command %p timed out\n", cmd);

	return BLK_EH_NOT_HANDLED;
}
