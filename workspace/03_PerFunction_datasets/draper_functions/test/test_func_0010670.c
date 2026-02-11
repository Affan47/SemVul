mmc_synchronize_cache(int host_no, struct scsi_cmd *cmd)
{
	struct mmc_info *mmc = dtype_priv(cmd->dev);

	if (mmc->current_profile == PROFILE_NO_PROFILE) {
		scsi_set_in_resid_by_actual(cmd, 0);
		sense_data_build(cmd, NOT_READY, ASC_MEDIUM_NOT_PRESENT);
		return SAM_STAT_CHECK_CONDITION;
	}

	return SAM_STAT_GOOD;
}
