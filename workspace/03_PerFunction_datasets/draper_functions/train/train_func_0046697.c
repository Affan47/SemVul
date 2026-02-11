wdt_keepalive(void)
{
	if (test_bit(WDTS_USE_GP, &wdt_status))
		inb(base);
	else if (test_bit(WDTS_USE_CIR, &wdt_status))

		outb(0x55, CIR_DR(base));
	else {
		if (superio_enter())
			return;

		superio_select(GPIO);
		wdt_update_timeout();
		superio_exit();
	}
	set_bit(WDTS_KEEPALIVE, &wdt_status);
}
