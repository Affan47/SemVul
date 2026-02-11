sd_stop_seq_mode(struct rtsx_chip *chip)
{
	struct sd_info *sd_card = &(chip->sd_card);
	int retval;

	if (sd_card->seq_mode) {
		retval = sd_switch_clock(chip);
		if (retval != STATUS_SUCCESS)
			return;

		retval = sd_send_cmd_get_rsp(chip, STOP_TRANSMISSION, 0,
				SD_RSP_TYPE_R1b, NULL, 0);
		if (retval != STATUS_SUCCESS)
			sd_set_err_code(chip, SD_STS_ERR);

		retval = sd_wait_state_data_ready(chip, 0x08, 1, 1000);
		if (retval != STATUS_SUCCESS)
			sd_set_err_code(chip, SD_STS_ERR);

		sd_card->seq_mode = 0;

		rtsx_write_register(chip, RBCTL, RB_FLUSH, RB_FLUSH);
	}
}
