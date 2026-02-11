sd_tuning_rx_cmd(struct rtsx_usb_sdmmc *host,
		u8 opcode, u8 sample_point)
{
	int err;
	struct mmc_command cmd = {0};

	err = sd_change_phase(host, sample_point, 0);
	if (err)
		return err;

	cmd.opcode = MMC_SEND_TUNING_BLOCK;
	err = sd_read_data(host, &cmd, 0x40, NULL, 0, 100);
	if (err) {

		sd_wait_data_idle(host);
		sd_clear_error(host);
		return err;
	}

	return 0;
}
