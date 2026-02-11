saa712x_write_regs(struct solo_dev *dev, const u8 *vals,
		int start, int n)
{
	for (; start < n; start++, vals++) {

		switch (start) {

		case 0x2e ... 0x37:
		case 0x60:
		case 0x7d:
			continue;
		}
		solo_i2c_writebyte(dev, SOLO_I2C_SAA, 0x46, start, *vals);
	}
}
