reg_r_12(struct gspca_dev *gspca_dev,
			__u16 req,
			__u16 index,
			__u16 length)
{
	int ret;

	gspca_dev->usb_buf[1] = 0;
	ret = usb_control_msg(gspca_dev->dev,
			usb_rcvctrlpipe(gspca_dev->dev, 0),
			req,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,
			index,
			gspca_dev->usb_buf, length,
			500);
	if (ret < 0) {
		pr_err("reg_r_12 err %d\n", ret);
		return ret;
	}
	return (gspca_dev->usb_buf[1] << 8) + gspca_dev->usb_buf[0];
}
