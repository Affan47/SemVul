vv6410_start(struct sd *sd)
{
	int err;
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;
	struct cam *cam = &sd->gspca_dev.cam;
	u32 priv = cam->cam_mode[sd->gspca_dev.curr_mode].priv;

	if (priv & VV6410_SUBSAMPLE) {
		PDEBUG(D_CONF, "Enabling subsampling");
		stv06xx_write_bridge(sd, STV_Y_CTRL, 0x02);
		stv06xx_write_bridge(sd, STV_X_CTRL, 0x06);

		stv06xx_write_bridge(sd, STV_SCAN_RATE, 0x10);
	} else {
		stv06xx_write_bridge(sd, STV_Y_CTRL, 0x01);
		stv06xx_write_bridge(sd, STV_X_CTRL, 0x0a);
		stv06xx_write_bridge(sd, STV_SCAN_RATE, 0x00);

	}


	err = stv06xx_write_bridge(sd, STV_LED_CTRL, LED_ON);
	if (err < 0)
		return err;

	err = stv06xx_write_sensor(sd, VV6410_SETUP0, 0);
	if (err < 0)
		return err;

	PDEBUG(D_STREAM, "Starting stream");

	return 0;
}
