af9035_wr_regs(struct dvb_usb_device *d, u32 reg, u8 *val, int len)
{
	u8 wbuf[MAX_XFER_SIZE];
	u8 mbox = (reg >> 16) & 0xff;
	struct usb_req req = { CMD_MEM_WR, mbox, 6 + len, wbuf, 0, NULL };

	if (6 + len > sizeof(wbuf)) {
		dev_warn(&d->udev->dev, "%s: i2c wr: len=%d is too big!\n",
			 KBUILD_MODNAME, len);
		return -EOPNOTSUPP;
	}

	wbuf[0] = len;
	wbuf[1] = 2;
	wbuf[2] = 0;
	wbuf[3] = 0;
	wbuf[4] = (reg >> 8) & 0xff;
	wbuf[5] = (reg >> 0) & 0xff;
	memcpy(&wbuf[6], val, len);

	return af9035_ctrl_msg(d, &req);
}
