vp702x_usb_in_op_unlocked(struct dvb_usb_device *d, u8 req,
				     u16 value, u16 index, u8 *b, int blen)
{
	int ret;

	ret = usb_control_msg(d->udev,
		usb_rcvctrlpipe(d->udev, 0),
		req,
		USB_TYPE_VENDOR | USB_DIR_IN,
		value, index, b, blen,
		2000);

	if (ret < 0) {
		warn("usb in operation failed. (%d)", ret);
		ret = -EIO;
	} else
		ret = 0;


	deb_xfer("in: req. %02x, val: %04x, ind: %04x, buffer: ",req,value,index);
	debug_dump(b,blen,deb_xfer);

	return ret;
}
