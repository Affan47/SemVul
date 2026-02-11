bs_sync_sync_range(struct scsi_cmd *cmd, uint32_t length,
			       int *result, uint8_t *key, uint16_t *asc)
{
	int ret;

	ret = fdatasync(cmd->dev->fd);
	if (ret)
		set_medium_error(result, key, asc);
}
