usbhs_bus_get_speed(struct usbhs_priv *priv)
{
	u16 dvstctr = usbhs_read(priv, DVSTCTR);

	switch (RHST & dvstctr) {
	case RHST_LOW_SPEED:
		return USB_SPEED_LOW;
	case RHST_FULL_SPEED:
		return USB_SPEED_FULL;
	case RHST_HIGH_SPEED:
		return USB_SPEED_HIGH;
	}

	return USB_SPEED_UNKNOWN;
}
