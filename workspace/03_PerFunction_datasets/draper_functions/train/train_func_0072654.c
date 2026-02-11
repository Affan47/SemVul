cpia_usb_transferCmd(struct gspca_dev *gspca_dev, u8 *command)
{
	u8 requesttype;
	unsigned int pipe;
	int ret, databytes = command[6] | (command[7] << 8);

	int retries = 3;

	if (command[0] == DATA_IN) {
		pipe = usb_rcvctrlpipe(gspca_dev->dev, 0);
		requesttype = USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE;
	} else if (command[0] == DATA_OUT) {
		pipe = usb_sndctrlpipe(gspca_dev->dev, 0);
		requesttype = USB_TYPE_VENDOR | USB_RECIP_DEVICE;
	} else {
		PERR("Unexpected first byte of command: %x", command[0]);
		return -EINVAL;
	}

retry:
	ret = usb_control_msg(gspca_dev->dev, pipe,
			      command[1],
			      requesttype,
			      command[2] | (command[3] << 8),
			      command[4] | (command[5] << 8),
			      gspca_dev->usb_buf, databytes, 1000);

	if (ret < 0)
		pr_err("usb_control_msg %02x, error %d\n", command[1], ret);

	if (ret == -EPIPE && retries > 0) {
		retries--;
		goto retry;
	}

	return (ret < 0) ? ret : 0;
}
