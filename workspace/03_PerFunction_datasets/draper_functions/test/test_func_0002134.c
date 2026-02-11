wdt_timer_ping(unsigned long data)
{


	if (time_before(jiffies, next_heartbeat)) {

		spin_lock(&wdt_spinlock);


		inb_p(WDT_PING);


		mod_timer(&timer, jiffies + WDT_INTERVAL);

		spin_unlock(&wdt_spinlock);

	} else
		pr_warn("Heartbeat lost! Will not ping the watchdog\n");
}
