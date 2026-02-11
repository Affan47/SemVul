lcd2usb_HD44780_backlight(PrivateData *p, unsigned char state)
{

	int promille = (state == BACKLIGHT_ON) ? p->brightness : p->offbrightness;

	p->hd44780_functions->drv_debug(RPT_DEBUG, "lcd2usb_HD44780_backlight: Setting backlight to %d", promille);


	if (usb_control_msg(p->usbHandle, USB_TYPE_VENDOR, LCD2USB_SET_BRIGHTNESS,
			    (promille * 255) / 1000, 0, NULL, 0, 1000) < 0)
		p->hd44780_functions->drv_report(RPT_WARNING, "lcd2usb_HD44780_backlight: setting backlight failed");
}
