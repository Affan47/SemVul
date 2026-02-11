sd_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct gspca_dev *gspca_dev =
		container_of(ctrl->handler, struct gspca_dev, ctrl_handler);
	struct sd *sd = (struct sd *)gspca_dev;

	gspca_dev->usb_err = 0;

	if (!gspca_dev->streaming)
		return 0;

	switch (ctrl->id) {
	case V4L2_CID_SHARPNESS:
		setsharpness(gspca_dev, ctrl->val);
		break;
	case V4L2_CID_GAMMA:
		setgamma(gspca_dev, ctrl->val);
		break;
	case V4L2_CID_BLUE_BALANCE:
		setbgain(gspca_dev, ctrl->val);
		break;
	case V4L2_CID_RED_BALANCE:
		setrgain(gspca_dev, ctrl->val);
		break;
	case V4L2_CID_EXPOSURE:
		sd_setgain(gspca_dev);
		break;
	case V4L2_CID_AUTOGAIN:
		if (ctrl->val)
			break;
		sd_setgain(gspca_dev);
		break;
	case V4L2_CID_JPEG_COMPRESSION_QUALITY:
		jpeg_set_qual(sd->jpeg_hdr, ctrl->val);
		break;
	}
	return gspca_dev->usb_err;
}
