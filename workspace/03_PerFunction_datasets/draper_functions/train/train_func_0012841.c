sd_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct gspca_dev *gspca_dev =
		container_of(ctrl->handler, struct gspca_dev, ctrl_handler);

	gspca_dev->usb_err = 0;

	if (!gspca_dev->streaming)
		return 0;

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		setbrightness(gspca_dev);
		break;
	case V4L2_CID_CONTRAST:
		setcontrast(gspca_dev);
		break;
	case V4L2_CID_SATURATION:
		setcolors(gspca_dev);
		break;
	case V4L2_CID_RED_BALANCE:
		setredblue(gspca_dev);
		break;
	case V4L2_CID_GAMMA:
		setgamma(gspca_dev);
		break;
	case V4L2_CID_AUTOGAIN:
		setautogain(gspca_dev);
		setexposure(gspca_dev);
		setgain(gspca_dev);
		break;
	case V4L2_CID_VFLIP:
		sethvflip(gspca_dev);
		break;
	case V4L2_CID_SHARPNESS:
		setsharpness(gspca_dev);
		break;
	case V4L2_CID_ILLUMINATORS_1:
		setillum(gspca_dev);
		break;
	case V4L2_CID_POWER_LINE_FREQUENCY:
		setfreq(gspca_dev);
		break;
	default:
		return -EINVAL;
	}
	return gspca_dev->usb_err;
}
