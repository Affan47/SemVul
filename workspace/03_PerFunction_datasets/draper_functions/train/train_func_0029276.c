rtsx_read_phy_register(struct rtsx_chip *chip, u8 addr, u16 *val)
{
	int retval;
	bool finished = false;
	int i;
	u16 data = 0;
	u8 tmp;

	retval = rtsx_write_register(chip, PHYADDR, 0xFF, addr);
	if (retval) {
		rtsx_trace(chip);
		return retval;
	}
	retval = rtsx_write_register(chip, PHYRWCTL, 0xFF, 0x80);
	if (retval) {
		rtsx_trace(chip);
		return retval;
	}

	for (i = 0; i < 100000; i++) {
		retval = rtsx_read_register(chip, PHYRWCTL, &tmp);
		if (retval) {
			rtsx_trace(chip);
			return retval;
		}
		if (!(tmp & 0x80)) {
			finished = true;
			break;
		}
	}

	if (!finished) {
		rtsx_trace(chip);
		return STATUS_FAIL;
	}

	retval = rtsx_read_register(chip, PHYDATA0, &tmp);
	if (retval) {
		rtsx_trace(chip);
		return retval;
	}
	data = tmp;
	retval = rtsx_read_register(chip, PHYDATA1, &tmp);
	if (retval) {
		rtsx_trace(chip);
		return retval;
	}
	data |= (u16)tmp << 8;

	if (val)
		*val = data;

	return STATUS_SUCCESS;
}
