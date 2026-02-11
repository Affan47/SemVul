msxc_change_power(struct rtsx_chip *chip, u8 mode)
{
	int retval;
	u8 buf[6];

	ms_cleanup_work(chip);

	retval = ms_set_rw_reg_addr(chip, 0, 0, Pro_DataCount1, 6);
	if (retval != STATUS_SUCCESS) {
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	buf[0] = 0;
	buf[1] = mode;
	buf[2] = 0;
	buf[3] = 0;
	buf[4] = 0;
	buf[5] = 0;

	retval = ms_write_bytes(chip, PRO_WRITE_REG, 6, NO_WAIT_INT, buf, 6);
	if (retval != STATUS_SUCCESS) {
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	retval = ms_send_cmd(chip, XC_CHG_POWER, WAIT_INT);
	if (retval != STATUS_SUCCESS) {
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	retval = rtsx_read_register(chip, MS_TRANS_CFG, buf);
	if (retval) {
		rtsx_trace(chip);
		return retval;
	}
	if (buf[0] & (MS_INT_CMDNK | MS_INT_ERR)) {
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	return STATUS_SUCCESS;
}
