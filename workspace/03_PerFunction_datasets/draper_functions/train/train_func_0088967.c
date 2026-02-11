ov9650_set_red_balance(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	u8 i2c_data;
	struct sd *sd = (struct sd *) gspca_dev;

	PDEBUG(D_CONF, "Set red gain to %d", val);

	i2c_data = val & 0xff;
	err = m5602_write_sensor(sd, OV9650_RED, &i2c_data, 1);
	return err;
}
