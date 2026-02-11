se401_read_req(struct gspca_dev *gspca_dev, u16 req, int silent)
{
	int err;

	if (gspca_dev->usb_err < 0)
		return;

	if (USB_BUF_SZ < READ_REQ_SIZE) {
		pr_err("USB_BUF_SZ too small!!\n");
		gspca_dev->usb_err = -ENOBUFS;
		return;
	}

	err = usb_control_msg(gspca_dev->dev,
			      usb_rcvctrlpipe(gspca_dev->dev, 0), req,
			      USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0, 0, gspca_dev->usb_buf, READ_REQ_SIZE, 1000);
	if (err < 0) {
		if (!silent)
			pr_err("read req failed req %#04x error %d\n",
			       req, err);
		gspca_dev->usb_err = err;
	}
}
