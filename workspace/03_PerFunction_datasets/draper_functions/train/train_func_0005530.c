space_filemark(struct scsi_cmd *cmd, int32_t count)
{
	struct ssc_info *ssc = dtype_priv(cmd->dev);
	struct blk_header_info *h = &ssc->c_blk;
	int result;

	dprintf("*** space %d filemarks, %" PRIu64 "\n", count, h->curr);

	if (count > 0)
		result = space_filemark_forward(cmd, count);
	else if (count < 0)
		result = space_filemark_reverse(cmd, count);
	else
		result = SAM_STAT_GOOD;

	dprintf("%" PRIu64 "\n", h->curr);

	return result;
}
