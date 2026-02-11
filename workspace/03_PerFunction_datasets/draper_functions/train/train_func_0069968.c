cdns_wdt_start(struct watchdog_device *wdd)
{
	struct cdns_wdt *wdt = watchdog_get_drvdata(wdd);
	unsigned int data = 0;
	unsigned short count;
	unsigned long clock_f = clk_get_rate(wdt->clk);


	count = (wdd->timeout * (clock_f / wdt->prescaler)) /
		 CDNS_WDT_COUNTER_VALUE_DIVISOR + 1;

	if (count > CDNS_WDT_COUNTER_MAX)
		count = CDNS_WDT_COUNTER_MAX;

	spin_lock(&wdt->io_lock);
	cdns_wdt_writereg(wdt, CDNS_WDT_ZMR_OFFSET,
			  CDNS_WDT_ZMR_ZKEY_VAL);

	count = (count << 2) & CDNS_WDT_CCR_CRV_MASK;


	data = count | CDNS_WDT_REGISTER_ACCESS_KEY | wdt->ctrl_clksel;
	cdns_wdt_writereg(wdt, CDNS_WDT_CCR_OFFSET, data);
	data = CDNS_WDT_ZMR_WDEN_MASK | CDNS_WDT_ZMR_RSTLEN_16 |
	       CDNS_WDT_ZMR_ZKEY_VAL;


	if (wdt->rst) {
		data |= CDNS_WDT_ZMR_RSTEN_MASK;
		data &= ~CDNS_WDT_ZMR_IRQEN_MASK;
	} else {
		data &= ~CDNS_WDT_ZMR_RSTEN_MASK;
		data |= CDNS_WDT_ZMR_IRQEN_MASK;
	}
	cdns_wdt_writereg(wdt, CDNS_WDT_ZMR_OFFSET, data);
	cdns_wdt_writereg(wdt, CDNS_WDT_RESTART_OFFSET,
			  CDNS_WDT_RESTART_KEY);
	spin_unlock(&wdt->io_lock);

	return 0;
}
