sd_check_data0_status(struct rtsx_chip *chip)
{
	int retval;
	u8 stat;

	retval = rtsx_read_register(chip, REG_SD_STAT1, &stat);
	if (retval) {
		rtsx_trace(chip);
		return retval;
	}

	if (!(stat & SD_DAT0_STATUS)) {
		sd_set_err_code(chip, SD_BUSY);
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	return STATUS_SUCCESS;
}
