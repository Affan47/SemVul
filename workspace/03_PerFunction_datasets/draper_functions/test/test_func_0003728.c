reg_rw(struct gspca_dev *gspca_dev,
		u8 bRequestType, u8 bRequest,
		u16 wValue, u16 wIndex, u16 wLength)
{
	struct usb_device *udev = gspca_dev->dev;
	int ret;

	if (gspca_dev->usb_err < 0)
		return;

	ret = usb_control_msg(udev,
		usb_rcvctrlpipe(udev, 0),
		bRequest,
		bRequestType,
		wValue, wIndex,
		gspca_dev->usb_buf, wLength, 500);

	if (ret < 0) {
		gspca_dev->usb_err = ret;
		pr_err("usb_control_msg error %d\n", ret);
	}

	return;
}
