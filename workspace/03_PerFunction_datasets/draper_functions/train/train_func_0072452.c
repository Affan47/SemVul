vv6410_set_exposure(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	struct sd *sd = (struct sd *) gspca_dev;
	unsigned int fine, coarse;

	val = (val * val >> 14) + val / 4;

	fine = val % VV6410_CIF_LINELENGTH;
	coarse = min(512, val / VV6410_CIF_LINELENGTH);

	PDEBUG(D_CONF, "Set coarse exposure to %d, fine exposure to %d",
	       coarse, fine);

	err = stv06xx_write_sensor(sd, VV6410_FINEH, fine >> 8);
	if (err < 0)
		goto out;

	err = stv06xx_write_sensor(sd, VV6410_FINEL, fine & 0xff);
	if (err < 0)
		goto out;

	err = stv06xx_write_sensor(sd, VV6410_COARSEH, coarse >> 8);
	if (err < 0)
		goto out;

	err = stv06xx_write_sensor(sd, VV6410_COARSEL, coarse & 0xff);

out:
	return err;
}
