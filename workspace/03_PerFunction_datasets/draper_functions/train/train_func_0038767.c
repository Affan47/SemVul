hfi1_set_led_override(struct hfi1_pportdata *ppd, unsigned int val)
{
	struct hfi1_devdata *dd = ppd->dd;
	int timeoff, freq;

	if (!(dd->flags & HFI1_INITTED))
		return;


	timeoff = HZ;
	freq = (val & LED_OVER_FREQ_MASK) >> LED_OVER_FREQ_SHIFT;

	if (freq) {

		ppd->led_override_vals[0] = val & 0xF;
		ppd->led_override_vals[1] = (val >> 4) & 0xF;
		timeoff = (HZ << 4)/freq;
	} else {

		ppd->led_override_vals[0] = val & 0xF;
		ppd->led_override_vals[1] = val & 0xF;
	}
	ppd->led_override_timeoff = timeoff;


	if (atomic_inc_return(&ppd->led_override_timer_active) == 1) {

		setup_timer(&ppd->led_override_timer, run_led_override,
				(unsigned long)ppd);

		ppd->led_override_timer.expires = jiffies + 1;
		add_timer(&ppd->led_override_timer);
	} else {
		if (ppd->led_override_vals[0] || ppd->led_override_vals[1])
			mod_timer(&ppd->led_override_timer, jiffies + 1);
		atomic_dec(&ppd->led_override_timer_active);
	}
}
