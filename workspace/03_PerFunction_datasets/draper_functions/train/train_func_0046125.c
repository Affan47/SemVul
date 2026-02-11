carl9170_led_update(struct work_struct *work)
{
	struct ar9170 *ar = container_of(work, struct ar9170, led_work.work);
	int i, tmp = 300, blink_delay = 1000;
	u32 led_val = 0;
	bool rerun = false;

	if (!IS_ACCEPTING_CMD(ar))
		return;

	mutex_lock(&ar->mutex);
	for (i = 0; i < AR9170_NUM_LEDS; i++) {
		if (ar->leds[i].registered) {
			if (ar->leds[i].last_state ||
			    ar->leds[i].toggled) {

				if (ar->leds[i].toggled)
					tmp = 70 + 200 / (ar->leds[i].toggled);

				if (tmp < blink_delay)
					blink_delay = tmp;

				led_val |= 1 << i;
				ar->leds[i].toggled = 0;
				rerun = true;
			}
		}
	}

	carl9170_led_set_state(ar, led_val);
	mutex_unlock(&ar->mutex);

	if (!rerun)
		return;

	ieee80211_queue_delayed_work(ar->hw,
				     &ar->led_work,
				     msecs_to_jiffies(blink_delay));
}
