goto_low_power(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int ret;

	ret = do_command(gspca_dev, CPIA_COMMAND_GotoLoPower, 0, 0, 0, 0);
	if (ret)
		return ret;

	ret = do_command(gspca_dev, CPIA_COMMAND_GetCameraStatus, 0, 0, 0, 0);
	if (ret)
		return ret;

	if (sd->params.status.systemState != LO_POWER_STATE) {
		if (sd->params.status.systemState != WARM_BOOT_STATE) {
			PERR("unexpected state after lo power cmd: %02x",
			     sd->params.status.systemState);
			printstatus(gspca_dev, &sd->params);
		}
		return -EIO;
	}

	PDEBUG(D_CONF, "camera now in LOW power state");
	return 0;
}
