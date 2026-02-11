ipath_set_led_override(struct ipath_devdata *dd, unsigned int val)
{
	int timeoff, freq;

	if (!(dd->ipath_flags & IPATH_INITTED))
		return;


	timeoff = HZ;
	freq = (val & LED_OVER_FREQ_MASK) >> LED_OVER_FREQ_SHIFT;

	if (freq) {

		dd->ipath_led_override_vals[0] = val & 0xF;
		dd->ipath_led_override_vals[1] = (val >> 4) & 0xF;
		timeoff = (HZ << 4)/freq;
	} else {

		dd->ipath_led_override_vals[0] = val & 0xF;
		dd->ipath_led_override_vals[1] = val & 0xF;
	}
	dd->ipath_led_override_timeoff = timeoff;


	if (atomic_inc_return(&dd->ipath_led_override_timer_active) == 1) {

		setup_timer(&dd->ipath_led_override_timer,
				ipath_run_led_override, (unsigned long)dd);

		dd->ipath_led_override_timer.expires = jiffies + 1;
		add_timer(&dd->ipath_led_override_timer);
	} else
		atomic_dec(&dd->ipath_led_override_timer_active);
}
