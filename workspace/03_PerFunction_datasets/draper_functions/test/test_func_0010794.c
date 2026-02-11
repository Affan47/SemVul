seems_rd_byte(void)
{
	int i;
	int rd_byte;
	unsigned char bits_2, bits_1;

	bits_1 = do_get_bits() | 2;
	do_set_bits(bits_1);

	rd_byte = 0;
	for (i = 0; i < 8; i++) {
		bits_1 &= 0xFE;
		do_set_bits(bits_1);
		cycle_delay(2);

		bits_1 |= 1;
		do_set_bits(bits_1);
		cycle_delay(1);

		bits_2 = do_get_bits();
		if (bits_2 & 2)
			rd_byte |= 1;

		rd_byte <<= 1;
	}

	bits_1 = 0;
	if (bits_2 == 0)
		bits_1 |= 2;

	do_set_bits(bits_1);
	cycle_delay(2);

	bits_1 |= 1;
	do_set_bits(bits_1);
	cycle_delay(3);

	bits_1 &= 0xFE;
	do_set_bits(bits_1);
	cycle_delay(2);

	rd_byte >>= 1;
	rd_byte &= 0xFF;
	return rd_byte;
}
