superio_enter(void)
{
	if (!request_muxed_region(wdt_io, 2, WATCHDOG_NAME))
		return -EBUSY;

	outb_p(0x87, WDT_EFER);
	outb_p(0x87, WDT_EFER);

	return 0;
}
