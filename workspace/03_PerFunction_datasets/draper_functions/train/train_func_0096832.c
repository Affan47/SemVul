encode_bMaxPower(enum usb_device_speed speed,
		struct usb_configuration *c)
{
	unsigned val;

	if (c->MaxPower)
		val = c->MaxPower;
	else
		val = CONFIG_USB_GADGET_VBUS_DRAW;
	if (!val)
		return 0;
	switch (speed) {
	case USB_SPEED_SUPER:
		return DIV_ROUND_UP(val, 8);
	default:
		return DIV_ROUND_UP(val, 2);
	}
}
