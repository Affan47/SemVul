sisusb_initialize(struct sisusb_usb_data *sisusb)
{

	if (sisusb_setidxreg(sisusb, SISCR, 0x0c, 0x00))
		return;
	if (sisusb_setidxreg(sisusb, SISCR, 0x0d, 0x00))
		return;
	if (sisusb_setidxreg(sisusb, SISCR, 0x0e, 0x00))
		return;
	sisusb_setidxreg(sisusb, SISCR, 0x0f, 0x00);
}
