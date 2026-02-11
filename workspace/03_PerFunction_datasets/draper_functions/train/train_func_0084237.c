rtsx_read_cfg_seq(struct rtsx_chip *chip, u8 func, u16 addr, u8 *buf,
		      int len)
{
	u32 *data;
	u16 offset = addr % 4;
	u16 aligned_addr = addr - offset;
	int dw_len, i, j;
	int retval;

	if ((len + offset) % 4)
		dw_len = (len + offset) / 4 + 1;
	else
		dw_len = (len + offset) / 4;

	dev_dbg(rtsx_dev(chip), "dw_len = %d\n", dw_len);

	data = vmalloc(dw_len * 4);
	if (!data) {
		rtsx_trace(chip);
		return STATUS_NOMEM;
	}

	for (i = 0; i < dw_len; i++) {
		retval = rtsx_read_cfg_dw(chip, func, aligned_addr + i * 4,
					  data + i);
		if (retval != STATUS_SUCCESS) {
			vfree(data);
			rtsx_trace(chip);
			return STATUS_FAIL;
		}
	}

	if (buf) {
		j = 0;

		for (i = 0; i < len; i++) {
			buf[i] = (u8)(data[j] >> (offset * 8));
			if (++offset == 4) {
				j++;
				offset = 0;
			}
		}
	}

	vfree(data);

	return STATUS_SUCCESS;
}
