sd_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct gspca_dev *gspca_dev =
		container_of(ctrl->handler, struct gspca_dev, ctrl_handler);

	gspca_dev->usb_err = 0;

	if (!gspca_dev->streaming)
		return 0;

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		setbrightness(gspca_dev, ctrl->val);
		break;
	case V4L2_CID_CONTRAST:
		setcontrast(gspca_dev, ctrl->val);
		break;
	case V4L2_CID_SATURATION:
		setcolors(gspca_dev, ctrl->val);
		break;
	case V4L2_CID_GAMMA:
		setgamma(gspca_dev, ctrl->val);
		break;
	case V4L2_CID_HFLIP:
		setmirror(gspca_dev, ctrl->val);
		break;
	case V4L2_CID_SHARPNESS:
		setsharpness(gspca_dev, ctrl->val);
		break;
	case V4L2_CID_POWER_LINE_FREQUENCY:
		setfreq(gspca_dev, ctrl->val);
		break;
	case V4L2_CID_BACKLIGHT_COMPENSATION:
		reg_w(gspca_dev, ctrl->val ? 0xf48e : 0xb48e);
		break;
	case V4L2_CID_AUTO_WHITE_BALANCE:
		setawb_n_RGB(gspca_dev);
		break;
	case V4L2_CID_COLORFX:
		seteffect(gspca_dev, ctrl->val);
		break;
	}
	return gspca_dev->usb_err;
}
