ftdi_HD44780_close(PrivateData *p)
{
    ftdi_disable_bitbang(&p->ftdic);
    ftdi_usb_close(&p->ftdic);
    ftdi_deinit(&p->ftdic);

    if (p->ftdi_mode == 8) {
	ftdi_disable_bitbang(&p->ftdic2);
	ftdi_usb_close(&p->ftdic2);
	ftdi_deinit(&p->ftdic2);
    }
}
