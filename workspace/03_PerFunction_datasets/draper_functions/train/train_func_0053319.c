feature_random_readable(struct scsi_cmd *cmd, char *data,
				     int only_current)
{
	struct mmc_info *mmc = dtype_priv(cmd->dev);
	int is_current;


	switch (mmc->current_profile) {
	case PROFILE_DVD_ROM:
		is_current = 1;
		break;
	default:
		is_current = 0;
	}

	if (only_current && !is_current)
		return data;


	*data++ = 0;
	*data++ = 0x10;


	*data = 0;
	if (is_current)
		*data |= 0x01;
	data++;


	*data++ = 8;


	*data++ = 0;
	*data++ = 0;
	*data++ = 8;
	*data++ = 0;


	*data++ = 0;
	*data++ = 0x10;


	*data++ = 0x01;


	*data++ = 0;

	return data;
}
