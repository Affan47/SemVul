sd_read_data(struct rtsx_chip *chip,
			u8 trans_mode, u8 *cmd, int cmd_len, u16 byte_cnt,
			u16 blk_cnt, u8 bus_width, u8 *buf, int buf_len,
			int timeout)
{
	struct sd_info *sd_card = &(chip->sd_card);
	int retval;
	int i;

	sd_clr_err_code(chip);

	if (!buf)
		buf_len = 0;

	if (buf_len > 512) {
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	rtsx_init_cmd(chip);

	if (cmd_len) {
		dev_dbg(rtsx_dev(chip), "SD/MMC CMD %d\n", cmd[0] - 0x40);
		for (i = 0; i < (cmd_len < 6 ? cmd_len : 6); i++)
			rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD0 + i,
				     0xFF, cmd[i]);
	}
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_L, 0xFF,
		(u8)byte_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BYTE_CNT_H, 0xFF,
		(u8)(byte_cnt >> 8));
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_L, 0xFF,
		(u8)blk_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_BLOCK_CNT_H, 0xFF,
		(u8)(blk_cnt >> 8));

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG1, 0x03, bus_width);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG2, 0xFF,
		SD_CALCULATE_CRC7 | SD_CHECK_CRC16 | SD_NO_WAIT_BUSY_END|
		SD_CHECK_CRC7 | SD_RSP_LEN_6);
	if (trans_mode != SD_TM_AUTO_TUNING)
		rtsx_add_cmd(chip, WRITE_REG_CMD,
			CARD_DATA_SOURCE, 0x01, PINGPONG_BUFFER);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER, 0xFF,
		trans_mode | SD_TRANSFER_START);
	rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER, SD_TRANSFER_END,
		SD_TRANSFER_END);

	retval = rtsx_send_cmd(chip, SD_CARD, timeout);
	if (retval < 0) {
		if (retval == -ETIMEDOUT) {
			sd_send_cmd_get_rsp(chip, SEND_STATUS, sd_card->sd_addr,
					    SD_RSP_TYPE_R1, NULL, 0);
		}

		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	if (buf && buf_len) {
		retval = rtsx_read_ppbuf(chip, buf, buf_len);
		if (retval != STATUS_SUCCESS) {
			rtsx_trace(chip);
			return STATUS_FAIL;
		}
	}

	return STATUS_SUCCESS;
}
