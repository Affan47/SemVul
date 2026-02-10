command_setlights(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int ret, p1, p2;

	p1 = (sd->params.qx3.bottomlight == 0) << 1;
	p2 = (sd->params.qx3.toplight == 0) << 3;

	ret = do_command(gspca_dev, CPIA_COMMAND_WriteVCReg,
			 0x90, 0x8f, 0x50, 0);
	if (ret)
		return ret;

	return do_command(gspca_dev, CPIA_COMMAND_WriteMCPort, 2, 0,
			  p1 | p2 | 0xe0, 0);
}
