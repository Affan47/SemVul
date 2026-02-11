sd_init_controls(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 4);

	gspca_dev->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,


		V4L2_CID_EXPOSURE, 0, 800, 1, 350);
	gspca_dev->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_GAIN, 0, 511, 1, 128);
	sd->blue = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BLUE_BALANCE, 0, 1023, 1, 80);
	sd->red = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_RED_BALANCE, 0, 1023, 1, 295);

	if (hdl->error) {
		PERR("Could not initialize controls\n");
		return hdl->error;
	}
	return 0;
}
