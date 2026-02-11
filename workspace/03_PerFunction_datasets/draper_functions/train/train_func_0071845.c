rtsx_write_cfg_dw(struct rtsx_chip *chip, u8 func_no, u16 addr, u32 mask,
		      u32 val)
{
	int retval;
	u8 mode = 0, tmp;
	int i;

	for (i = 0; i < 4; i++) {
		if (mask & 0xFF) {
			retval = rtsx_write_register(chip, CFGDATA0 + i,
						     0xFF,
						     (u8)(val & mask & 0xFF));
			if (retval) {
				rtsx_trace(chip);
				return retval;
			}
			mode |= (1 << i);
		}
		mask >>= 8;
		val >>= 8;
	}

	if (mode) {
		retval = rtsx_write_register(chip, CFGADDR0, 0xFF, (u8)addr);
		if (retval) {
			rtsx_trace(chip);
			return retval;
		}
		retval = rtsx_write_register(chip, CFGADDR1, 0xFF,
					     (u8)(addr >> 8));
		if (retval) {
			rtsx_trace(chip);
			return retval;
		}

		retval = rtsx_write_register(chip, CFGRWCTL, 0xFF,
					     0x80 | mode | ((func_no & 0x03) << 4));
		if (retval) {
			rtsx_trace(chip);
			return retval;
		}

		for (i = 0; i < MAX_RW_REG_CNT; i++) {
			retval = rtsx_read_register(chip, CFGRWCTL, &tmp);
			if (retval) {
				rtsx_trace(chip);
				return retval;
			}
			if ((tmp & 0x80) == 0)
				break;
		}
	}

	return STATUS_SUCCESS;
}
