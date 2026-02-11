anysee_rc_query(struct dvb_usb_device *d)
{
	u8 buf[] = {CMD_GET_IR_CODE};
	u8 ircode[2];
	int ret;


	ret = anysee_ctrl_msg(d, buf, sizeof(buf), ircode, sizeof(ircode));
	if (ret)
		return ret;

	if (ircode[0]) {
		dev_dbg(&d->udev->dev, "%s: key pressed %02x\n", __func__,
				ircode[1]);
		rc_keydown(d->rc_dev, RC_TYPE_NEC,
			   RC_SCANCODE_NEC(0x08, ircode[1]), 0);
	}

	return 0;
}
