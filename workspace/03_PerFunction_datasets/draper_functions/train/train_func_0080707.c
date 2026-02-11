__rpipe_reset(struct wahc *wa, unsigned index)
{
	int result;
	struct device *dev = &wa->usb_iface->dev;

	result = usb_control_msg(
		wa->usb_dev, usb_sndctrlpipe(wa->usb_dev, 0),
		USB_REQ_RPIPE_RESET,
		USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_RPIPE,
		0, index, NULL, 0, USB_CTRL_SET_TIMEOUT);
	if (result < 0)
		dev_err(dev, "rpipe %u: reset failed: %d\n",
			index, result);
	return result;
}
