reg_r(struct gspca_dev *gspca_dev,
			__u16 index)
{
	struct usb_device *dev = gspca_dev->dev;
	int ret;

	if (gspca_dev->usb_err < 0)
		return 0;
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			0x00,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0x00,
			index,
			gspca_dev->usb_buf, 1,
			500);
	if (ret < 0) {
		pr_err("reg_r err %d\n", ret);
		gspca_dev->usb_err = ret;
		return 0;
	}
	return gspca_dev->usb_buf[0];
}
