sch311x_wdt_set_timeout(int t)
{
	unsigned char timeout_unit = 0x80;


	if (t > 255) {
		timeout_unit = 0;
		t /= 60;
	}


	outb(timeout_unit, sch311x_wdt_data.runtime_reg + WDT_TIME_OUT);


	outb(t, sch311x_wdt_data.runtime_reg + WDT_VAL);
}
