mos7840_get_reg(struct moschip_port *mcs, __u16 Wval, __u16 reg,
			   __u16 *val)
{
	struct usb_device *dev = mcs->port->serial->dev;
	struct usb_ctrlrequest *dr = mcs->dr;
	unsigned char *buffer = mcs->ctrl_buf;
	int ret;

	if (test_and_set_bit_lock(MOS7840_FLAG_CTRL_BUSY, &mcs->flags))
		return -EBUSY;

	dr->bRequestType = MCS_RD_RTYPE;
	dr->bRequest = MCS_RDREQ;
	dr->wValue = cpu_to_le16(Wval);
	dr->wIndex = cpu_to_le16(reg);
	dr->wLength = cpu_to_le16(2);

	usb_fill_control_urb(mcs->control_urb, dev, usb_rcvctrlpipe(dev, 0),
			     (unsigned char *)dr, buffer, 2,
			     mos7840_control_callback, mcs);
	mcs->control_urb->transfer_buffer_length = 2;
	ret = usb_submit_urb(mcs->control_urb, GFP_ATOMIC);
	if (ret)
		clear_bit_unlock(MOS7840_FLAG_CTRL_BUSY, &mcs->flags);

	return ret;
}
