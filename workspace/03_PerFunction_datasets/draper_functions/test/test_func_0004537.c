anysee_ir_ctrl(struct dvb_usb_device *d, u8 onoff)
{
	u8 buf[] = {CMD_LED_AND_IR_CTRL, 0x02, onoff};
	dev_dbg(&d->udev->dev, "%s: onoff=%d\n", __func__, onoff);
	return anysee_ctrl_msg(d, buf, sizeof(buf), NULL, 0);
}
