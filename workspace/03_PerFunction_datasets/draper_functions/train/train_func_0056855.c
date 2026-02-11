rtsx_reset_aspm(struct rtsx_chip *chip)
{
	int ret;

	if (chip->dynamic_aspm) {
		if (!CHK_SDIO_EXIST(chip) || !CHECK_PID(chip, 0x5288))
			return STATUS_SUCCESS;

		ret = rtsx_write_cfg_dw(chip, 2, 0xC0, 0xFF,
					chip->aspm_l0s_l1_en);
		if (ret != STATUS_SUCCESS) {
			rtsx_trace(chip);
			return STATUS_FAIL;
		}

		return STATUS_SUCCESS;
	}

	if (CHECK_PID(chip, 0x5208)) {
		ret = rtsx_write_register(chip, ASPM_FORCE_CTL, 0xFF, 0x3F);
		if (ret) {
			rtsx_trace(chip);
			return ret;
		}
	}
	ret = rtsx_write_config_byte(chip, LCTLR, chip->aspm_l0s_l1_en);
	if (ret != STATUS_SUCCESS) {
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	chip->aspm_level[0] = chip->aspm_l0s_l1_en;
	if (CHK_SDIO_EXIST(chip)) {
		chip->aspm_level[1] = chip->aspm_l0s_l1_en;
		ret = rtsx_write_cfg_dw(chip, CHECK_PID(chip, 0x5288) ? 2 : 1,
					0xC0, 0xFF, chip->aspm_l0s_l1_en);
		if (ret != STATUS_SUCCESS) {
			rtsx_trace(chip);
			return STATUS_FAIL;
		}
	}

	chip->aspm_enabled = 1;

	return STATUS_SUCCESS;
}
