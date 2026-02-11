reg_r(struct gspca_dev *gspca_dev,
			u8 req,
			u16 index,
			int len)
{
#if USB_BUF_SZ < 64
#error "USB buffer too small"
#endif
	struct usb_device *dev = gspca_dev->dev;
	int ret;

	if (gspca_dev->usb_err < 0)
		return;
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			req,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0x0000,
			index,
			gspca_dev->usb_buf, len,
			500);
	PDEBUG(D_USBI, "GET %02x 0000 %04x %02x", req, index,
			 gspca_dev->usb_buf[0]);
	if (ret < 0) {
		pr_err("reg_r err %d\n", ret);
		gspca_dev->usb_err = ret;
	}
}
