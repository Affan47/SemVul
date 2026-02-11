seems_wr_byte(unsigned char value)
{
	int i;
	unsigned char reg;

	reg = do_get_bits();
	for (i = 0; i < 8; i++) {
		if (value & 0x80)
			reg |= 0x02;
		else
			reg &= 0xFD;

		do_set_bits(reg);
		cycle_delay(1);

		reg |= 1;
		do_set_bits(reg);
		cycle_delay(1);

		reg &= 0xFE;
		do_set_bits(reg);
		cycle_delay(1);
		value <<= 1;
	}
	cycle_delay(2);

	reg |= 2;
	do_set_bits(reg);

	reg |= 1;
	do_set_bits(reg);

	cycle_delay(1);
	do_get_bits();

	reg &= 0xFE;
	do_set_bits(reg);
	cycle_delay(3);
}
