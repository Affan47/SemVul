reg_w_buf(struct gspca_dev *gspca_dev,
			const u8 *cmd)
{
	u16 reg;
	int len;

	for (;;) {
		reg = *cmd++ << 8;
		reg += *cmd++;
		len = *cmd++;
		if (len == 0)
			break;
		if (cmd[-3] != I2C0)
			reg_w(gspca_dev, reg, cmd, len);
		else
			i2c_w(gspca_dev, reg, cmd, len);
		cmd += len;
	}
}
