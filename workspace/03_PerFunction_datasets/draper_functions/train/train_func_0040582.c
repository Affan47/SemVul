mg_chg(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	struct ms_info *ms_card = &(chip->ms_card);
	int retval;
	int bufflen;
	int i;
	unsigned int lun = SCSI_LUN(srb);
	u8 buf[32];

	ms_cleanup_work(chip);

	retval = ms_switch_clock(chip);
	if (retval != STATUS_SUCCESS) {
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	retval = mg_send_ex_cmd(chip, MG_GET_ID, 0);
	if (retval != STATUS_SUCCESS) {
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	retval = ms_read_bytes(chip, PRO_READ_SHORT_DATA, 32, WAIT_INT,
			buf, 32);
	if (retval != STATUS_SUCCESS) {
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		rtsx_trace(chip);
		return STATUS_FAIL;
	}
	if (check_ms_err(chip)) {
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		rtsx_clear_ms_error(chip);
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	memcpy(ms_card->magic_gate_id, buf, 16);

#ifdef READ_BYTES_WAIT_INT
	retval = ms_poll_int(chip);
	if (retval != STATUS_SUCCESS) {
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		rtsx_trace(chip);
		return STATUS_FAIL;
	}
#endif

	retval = mg_send_ex_cmd(chip, MG_SET_RD, 0);
	if (retval != STATUS_SUCCESS) {
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	bufflen = min_t(int, 12, scsi_bufflen(srb));
	rtsx_stor_get_xfer_buf(buf, bufflen, srb);

	for (i = 0; i < 8; i++)
		buf[i] = buf[4+i];

	for (i = 0; i < 24; i++)
		buf[8+i] = 0;

	retval = ms_write_bytes(chip, PRO_WRITE_SHORT_DATA,
				32, WAIT_INT, buf, 32);
	if (retval != STATUS_SUCCESS) {
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		rtsx_trace(chip);
		return STATUS_FAIL;
	}
	if (check_ms_err(chip)) {
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		rtsx_clear_ms_error(chip);
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	ms_card->mg_auth = 0;

	return STATUS_SUCCESS;
}
