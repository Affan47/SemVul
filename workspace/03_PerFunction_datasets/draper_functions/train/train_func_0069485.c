ov9650_set_hvflip(struct gspca_dev *gspca_dev)
{
	int err;
	u8 i2c_data;
	struct sd *sd = (struct sd *) gspca_dev;
	int hflip = sd->hflip->val;
	int vflip = sd->vflip->val;

	PDEBUG(D_CONF, "Set hvflip to %d %d", hflip, vflip);

	if (dmi_check_system(ov9650_flip_dmi_table))
		vflip = !vflip;

	i2c_data = (hflip << 5) | (vflip << 4);
	err = m5602_write_sensor(sd, OV9650_MVFP, &i2c_data, 1);
	if (err < 0)
		return err;


	if (gspca_dev->streaming)
		err = ov9650_start(sd);

	return err;
}
