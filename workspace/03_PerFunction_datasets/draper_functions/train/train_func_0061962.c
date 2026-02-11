sd_init_controls_72a(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *)gspca_dev;
	struct v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 4);
	sd->contrast = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 0x3f, 1, 0x20);
	sd->hue = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_HUE, 1, 0x7f, 1, 0x40);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 0x3f, 1, 0x20);
	sd->autogain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);

	if (hdl->error) {
		pr_err("Could not initialize controls\n");
		return hdl->error;
	}
	v4l2_ctrl_cluster(2, &sd->contrast);
	return 0;
}
