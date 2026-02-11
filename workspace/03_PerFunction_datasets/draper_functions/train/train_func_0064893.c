it8712f_wdt_get_status(void)
{
	if (superio_inb(WDT_CONTROL) & 0x01)
		return WDIOF_CARDRESET;
	else
		return 0;
}
