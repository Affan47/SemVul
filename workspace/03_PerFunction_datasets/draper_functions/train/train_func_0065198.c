uv_rtc_init(void)
{
	long status;
	u64 ticks_per_sec;

	status = uv_bios_freq_base(BIOS_FREQ_BASE_REALTIME_CLOCK,
					&ticks_per_sec);
	if (status != BIOS_STATUS_SUCCESS || ticks_per_sec < 100000) {
		printk(KERN_WARNING
			"unable to determine platform RTC clock frequency, "
			"guessing.\n");

		sn_rtc_cycles_per_second = 1000000000000UL / 30000UL;
	} else
		sn_rtc_cycles_per_second = ticks_per_sec;
}
