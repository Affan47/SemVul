rd_byte(struct ipath_devdata *dd)
{
	int bit_cntr, data;

	data = 0;

	for (bit_cntr = 7; bit_cntr >= 0; --bit_cntr) {
		data <<= 1;
		scl_out(dd, i2c_line_high);
		data |= sda_in(dd, 0);
		scl_out(dd, i2c_line_low);
	}
	return data;
}
