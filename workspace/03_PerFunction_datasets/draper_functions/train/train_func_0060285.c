speedtch_start_synchro(struct speedtch_instance_data *instance)
{
	struct usbatm_data *usbatm = instance->usbatm;
	struct usb_device *usb_dev = usbatm->usb_dev;
	unsigned char *buf = instance->scratch_buffer;
	int ret;

	atm_dbg(usbatm, "%s entered\n", __func__);

	memset(buf, 0, 2);

	ret = usb_control_msg(usb_dev, usb_rcvctrlpipe(usb_dev, 0),
			      0x12, 0xc0, 0x04, 0x00,
			      buf, 2, CTRL_TIMEOUT);

	if (ret < 0)
		atm_warn(usbatm, "failed to start ADSL synchronisation: %d\n", ret);
	else
		atm_dbg(usbatm, "%s: modem prodded. %d bytes returned: %02x %02x\n",
			__func__, ret, buf[0], buf[1]);

	return ret;
}
