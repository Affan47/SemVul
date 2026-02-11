altera_check_crc(u8 *p, s32 program_size)
{
	int status = 0;
	u16 local_expected = 0,
	    local_actual = 0,
	    shift_reg = 0xffff;
	int bit, feedback;
	u8 databyte;
	u32 i;
	u32 crc_section = 0L;
	u32 first_word = 0L;
	int version = 0;
	int delta = 0;

	if (program_size > 52L) {
		first_word  = get_unaligned_be32(&p[0]);
		version = (first_word & 1L);
		delta = version * 8;

		crc_section = get_unaligned_be32(&p[32 + delta]);
	}

	if ((first_word != 0x4A414D00L) && (first_word != 0x4A414D01L))
		status = -EIO;

	if (crc_section >= program_size)
		status = -EIO;

	if (status == 0) {
		local_expected = (u16)get_unaligned_be16(&p[crc_section]);

		for (i = 0; i < crc_section; ++i) {
			databyte = p[i];
			for (bit = 0; bit < 8; bit++) {
				feedback = (databyte ^ shift_reg) & 0x01;
				shift_reg >>= 1;
				if (feedback)
					shift_reg ^= 0x8408;

				databyte >>= 1;
			}
		}

		local_actual = (u16)~shift_reg;

		if (local_expected != local_actual)
			status = -EILSEQ;

	}

	if (debug || status) {
		switch (status) {
		case 0:
			printk(KERN_INFO "%s: CRC matched: %04x\n", __func__,
				local_actual);
			break;
		case -EILSEQ:
			printk(KERN_ERR "%s: CRC mismatch: expected %04x, "
				"actual %04x\n", __func__, local_expected,
				local_actual);
			break;
		case -ENODATA:
			printk(KERN_ERR "%s: expected CRC not found, "
				"actual CRC = %04x\n", __func__,
				local_actual);
			break;
		case -EIO:
			printk(KERN_ERR "%s: error: format isn't "
				"recognized.\n", __func__);
			break;
		default:
			printk(KERN_ERR "%s: CRC function returned error "
				"code %d\n", __func__, status);
			break;
		}
	}

	return status;
}
