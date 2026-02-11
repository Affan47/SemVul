reg_r_i(struct gspca_dev *gspca_dev,
		  u16 req,
		  u16 index,
		  u16 len)
{
	int ret;

	if (gspca_dev->usb_err < 0)
		return;
	ret = usb_control_msg(gspca_dev->dev,
			usb_rcvctrlpipe(gspca_dev->dev, 0),
			req,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			1,
			index, gspca_dev->usb_buf, len,
			500);
	if (ret < 0) {
		pr_err("reg_r err %d\n", ret);
		gspca_dev->usb_err = ret;
	}
}
