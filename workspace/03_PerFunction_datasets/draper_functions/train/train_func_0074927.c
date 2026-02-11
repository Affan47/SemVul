sd_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct gspca_dev *gspca_dev =
		container_of(ctrl->handler, struct gspca_dev, ctrl_handler);
	struct sd *sd = (struct sd *)gspca_dev;
	s32 red_gain, blue_gain, green_gain;

	gspca_dev->usb_err = 0;

	switch (ctrl->id) {
	case V4L2_CID_AUTO_WHITE_BALANCE:
		red_gain = reg_r(gspca_dev, 0x0087);
		if (red_gain > 0x40)
			red_gain = 0x40;
		else if (red_gain < 0x10)
			red_gain = 0x10;

		blue_gain = reg_r(gspca_dev, 0x0088);
		if (blue_gain > 0x40)
			blue_gain = 0x40;
		else if (blue_gain < 0x10)
			blue_gain = 0x10;

		green_gain = reg_r(gspca_dev, 0x0089);
		if (green_gain > 0x40)
			green_gain = 0x40;
		else if (green_gain < 0x10)
			green_gain = 0x10;

		sd->gain->val = green_gain;
		sd->red_balance->val = red_gain - green_gain;
		sd->blue_balance->val = blue_gain - green_gain;
		break;
	}
	return 0;
}
