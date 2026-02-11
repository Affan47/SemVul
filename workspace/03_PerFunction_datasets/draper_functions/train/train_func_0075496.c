usbvision_power_off(struct usb_usbvision *usbvision)
{
	int err_code = 0;

	PDEBUG(DBG_FUNC, "");

	err_code = usbvision_write_reg(usbvision, USBVISION_PWR_REG, USBVISION_SSPND_EN);
	if (err_code == 1)
		usbvision->power = 0;
	PDEBUG(DBG_FUNC, "%s: err_code %d", (err_code != 1) ? "ERROR" : "power is off", err_code);
	return err_code;
}
