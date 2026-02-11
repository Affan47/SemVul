sq905_ack_frame(struct gspca_dev *gspca_dev)
{
	int ret;

	gspca_dev->usb_buf[0] = '\0';
	ret = usb_control_msg(gspca_dev->dev,
			      usb_sndctrlpipe(gspca_dev->dev, 0),
			      USB_REQ_SYNCH_FRAME,
			      USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      SQ905_READ_DONE, 0, gspca_dev->usb_buf, 1,
			      SQ905_CMD_TIMEOUT);
	if (ret < 0) {
		pr_err("%s: usb_control_msg failed (%d)\n", __func__, ret);
		return ret;
	}

	return 0;
}
