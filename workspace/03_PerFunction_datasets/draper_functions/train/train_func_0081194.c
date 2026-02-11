ie6xx_wdt_stop(struct watchdog_device *wdd)
{
	if (inb(ie6xx_wdt_data.sch_wdtba + WDTLR) & WDT_LOCK)
		return -1;


	spin_lock(&ie6xx_wdt_data.unlock_sequence);
	outb(0, ie6xx_wdt_data.sch_wdtba + WDTLR);
	spin_unlock(&ie6xx_wdt_data.unlock_sequence);

	return 0;
}
