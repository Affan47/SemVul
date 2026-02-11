ov7660_set_gain(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	u8 i2c_data = val;
	struct sd *sd = (struct sd *) gspca_dev;

	PDEBUG(D_CONF, "Setting gain to %d", val);

	err = m5602_write_sensor(sd, OV7660_GAIN, &i2c_data, 1);
	return err;
}
