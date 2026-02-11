space_blocks(struct scsi_cmd *cmd, int32_t count)
{
	struct ssc_info *ssc = dtype_priv(cmd->dev);
	struct blk_header_info *h = &ssc->c_blk;

	dprintf("*** space %d blocks, %" PRIu64 "\n", count, h->curr);

	while (count != 0) {
		if (count > 0) {
			if (skip_next_header(cmd->dev)) {
				sense_data_build(cmd, MEDIUM_ERROR,
						ASC_MEDIUM_FORMAT_CORRUPT);
				return SAM_STAT_CHECK_CONDITION;
			}
			if (h->blk_type == BLK_EOD) {
				sense_data_build(cmd, NO_SENSE,
						ASC_END_OF_DATA);
				return SAM_STAT_CHECK_CONDITION;
			}
			count--;
		} else {
			if (skip_prev_header(cmd->dev)) {
				sense_data_build(cmd, MEDIUM_ERROR,
						ASC_MEDIUM_FORMAT_CORRUPT);
				return SAM_STAT_CHECK_CONDITION;
			}
			if (h->blk_type == BLK_BOT) {

				skip_next_header(cmd->dev);

				sense_data_build(cmd, NO_SENSE, ASC_BOM);
				return SAM_STAT_CHECK_CONDITION;
			}
			count++;
		}
	}
	dprintf("%" PRIu64 "\n", h->curr);
	return SAM_STAT_GOOD;
}
