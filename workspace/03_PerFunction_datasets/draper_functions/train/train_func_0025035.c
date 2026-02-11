mmc_read_capacity(int host_no, struct scsi_cmd *cmd)
{
	struct mmc_info *mmc = dtype_priv(cmd->dev);
	uint64_t size;
	uint32_t *data;

	if (mmc->current_profile == PROFILE_NO_PROFILE) {
		scsi_set_in_resid_by_actual(cmd, 0);
		sense_data_build(cmd, NOT_READY, ASC_MEDIUM_NOT_PRESENT);
		return SAM_STAT_CHECK_CONDITION;
	}

	if (scsi_get_in_length(cmd) < 8)
		goto overflow;

	data = scsi_get_in_buffer(cmd);
	size = cmd->dev->size >> MMC_BLK_SHIFT;

	if (size)
		data[0] = (size >> 32) ?
			__cpu_to_be32(0xffffffff) : __cpu_to_be32(size - 1);
	else
		data[0] = 0;

	data[1] = __cpu_to_be32(1U << MMC_BLK_SHIFT);
overflow:
	scsi_set_in_resid_by_actual(cmd, 8);
	return SAM_STAT_GOOD;
}
