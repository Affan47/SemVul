i2c_w_seq(struct gspca_dev *gspca_dev,
			const u8 (*data)[8])
{
	while ((*data)[0] != 0) {
		if ((*data)[0] != DELAY)
			i2c_w8(gspca_dev, *data);
		else
			msleep((*data)[1]);
		data++;
	}
}
