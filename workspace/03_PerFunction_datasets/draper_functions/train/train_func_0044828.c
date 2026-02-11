reg_w_ixbuf(struct gspca_dev *gspca_dev,
			u8 reg,
			const u8 *buffer, u16 len)
{
	int i;
	u8 *p, *tmpbuf;

	if (len * 2 <= USB_BUF_SZ) {
		p = tmpbuf = gspca_dev->usb_buf;
	} else {
		p = tmpbuf = kmalloc(len * 2, GFP_KERNEL);
		if (!tmpbuf) {
			pr_err("Out of memory\n");
			return;
		}
	}
	i = len;
	while (--i >= 0) {
		*p++ = reg++;
		*p++ = *buffer++;
	}
	usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0x01, 0,
			tmpbuf, len * 2, 500);
	if (len * 2 > USB_BUF_SZ)
		kfree(tmpbuf);
}
