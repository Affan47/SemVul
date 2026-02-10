setgain(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->sensor == SENSOR_PO2030N) {
		u8 rgain[] =
			{0xa1, 0x6e, 0x15, 0x00, 0x40, 0x00, 0x00, 0x15};

		rgain[3] = gspca_dev->gain->val;
		i2c_w8(gspca_dev, rgain);
	}
}
