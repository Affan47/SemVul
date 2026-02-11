ssd_send_cmd_db(struct ssd_cmd *cmd)
{
	struct ssd_device *dev = (struct ssd_device *)cmd->dev;
	struct bio *bio = cmd->bio;

	ssd_cmd_add_timer(cmd, SSD_CMD_TIMEOUT, ssd_cmd_timeout);

	if (bio) {
		switch (dev->db_info.type) {
			case SSD_DEBUG_READ_TO:
				if (bio_data_dir(bio) == READ) {
					return;
				}
				break;
			case SSD_DEBUG_WRITE_TO:
				if (bio_data_dir(bio) == WRITE) {
					return;
				}
				break;
			case SSD_DEBUG_RW_TO:
				return;
				break;
			default:
				break;
		}
	}

	ssd_reg32_write(dev->ctrlp + SSD_REQ_FIFO_REG, ((uint32_t)cmd->tag | ((uint32_t)cmd->nsegs << 16)));
}
