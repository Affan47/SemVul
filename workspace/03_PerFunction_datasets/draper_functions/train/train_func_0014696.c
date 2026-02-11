reg_read(struct gspca_dev *gspca_dev,
			u16 index)
{
	int ret;

	ret = usb_control_msg(gspca_dev->dev,
			usb_rcvctrlpipe(gspca_dev->dev, 0),
			0,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,
			index,
			gspca_dev->usb_buf, 1,
			500);
	PDEBUG(D_USBI, "reg read i:%04x --> %02x",
		index, gspca_dev->usb_buf[0]);
	if (ret < 0) {
		pr_err("reg_read err %d\n", ret);
		return ret;
	}
	return gspca_dev->usb_buf[0];
}
