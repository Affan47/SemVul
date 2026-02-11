sbc_sync_cache(int host_no, struct scsi_cmd *cmd)
{
	int ret, len;
	uint8_t key = ILLEGAL_REQUEST;
	uint16_t asc = ASC_LUN_NOT_SUPPORTED;

	if (device_reserved(cmd))
		return SAM_STAT_RESERVATION_CONFLICT;

	cmd->scsi_cmd_done = target_cmd_io_done;

	ret = cmd->dev->bst->bs_cmd_submit(cmd);
	switch (ret) {
	case EROFS:
	case EINVAL:
	case EBADF:
	case EIO:


		key = HARDWARE_ERROR;
		asc = ASC_INTERNAL_TGT_FAILURE;
		goto sense;
	default:
		len = 0;
		return SAM_STAT_GOOD;
	}

sense:
	scsi_set_in_resid_by_actual(cmd, 0);
	sense_data_build(cmd, key, asc);
	return SAM_STAT_CHECK_CONDITION;
}
