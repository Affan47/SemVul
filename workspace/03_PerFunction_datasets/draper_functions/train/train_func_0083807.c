set_chip_mode(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	int phy_debug_mode;
	int retval;
	u16 reg;

	if (!CHECK_PID(chip, 0x5208)) {
		set_sense_type(chip, SCSI_LUN(srb),
			SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		rtsx_trace(chip);
		return TRANSPORT_FAILED;
	}

	phy_debug_mode = (int)(srb->cmnd[3]);

	if (phy_debug_mode) {
		chip->phy_debug_mode = 1;
		retval = rtsx_write_register(chip, CDRESUMECTL, 0x77, 0);
		if (retval != STATUS_SUCCESS) {
			rtsx_trace(chip);
			return TRANSPORT_FAILED;
		}

		rtsx_disable_bus_int(chip);

		retval = rtsx_read_phy_register(chip, 0x1C, &reg);
		if (retval != STATUS_SUCCESS) {
			rtsx_trace(chip);
			return TRANSPORT_FAILED;
		}

		reg |= 0x0001;
		retval = rtsx_write_phy_register(chip, 0x1C, reg);
		if (retval != STATUS_SUCCESS) {
			rtsx_trace(chip);
			return TRANSPORT_FAILED;
		}
	} else {
		chip->phy_debug_mode = 0;
		retval = rtsx_write_register(chip, CDRESUMECTL, 0x77, 0x77);
		if (retval != STATUS_SUCCESS) {
			rtsx_trace(chip);
			return TRANSPORT_FAILED;
		}

		rtsx_enable_bus_int(chip);

		retval = rtsx_read_phy_register(chip, 0x1C, &reg);
		if (retval != STATUS_SUCCESS) {
			rtsx_trace(chip);
			return TRANSPORT_FAILED;
		}

		reg &= 0xFFFE;
		retval = rtsx_write_phy_register(chip, 0x1C, reg);
		if (retval != STATUS_SUCCESS) {
			rtsx_trace(chip);
			return TRANSPORT_FAILED;
		}
	}

	return TRANSPORT_GOOD;
}
