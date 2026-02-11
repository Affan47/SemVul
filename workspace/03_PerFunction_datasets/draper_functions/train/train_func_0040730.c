sd_init_controls(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *)gspca_dev;
	struct v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;
	static const char * const comp_target_menu[] = {
		"Quality",
		"Framerate",
		NULL
	};
	static const struct v4l2_ctrl_config comp_target = {
		.ops = &sd_ctrl_ops,
		.id = CPIA1_CID_COMP_TARGET,
		.type = V4L2_CTRL_TYPE_MENU,
		.name = "Compression Target",
		.qmenu = comp_target_menu,
		.max = 1,
		.def = COMP_TARGET_DEF,
	};

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 7);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 100, 1, BRIGHTNESS_DEF);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 96, 8, CONTRAST_DEF);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SATURATION, 0, 100, 1, SATURATION_DEF);
	sd->freq = v4l2_ctrl_new_std_menu(hdl, &sd_ctrl_ops,
			V4L2_CID_POWER_LINE_FREQUENCY,
			V4L2_CID_POWER_LINE_FREQUENCY_60HZ, 0,
			FREQ_DEF);
	if (sd->params.qx3.qx3_detected) {
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_ILLUMINATORS_1, 0, 1, 1,
				ILLUMINATORS_1_DEF);
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_ILLUMINATORS_2, 0, 1, 1,
				ILLUMINATORS_2_DEF);
	}
	v4l2_ctrl_new_custom(hdl, &comp_target, NULL);

	if (hdl->error) {
		pr_err("Could not initialize controls\n");
		return hdl->error;
	}
	return 0;
}
