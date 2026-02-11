p54_update_leds(struct work_struct *work)
{
	struct p54_common *priv = container_of(work, struct p54_common,
					       led_work.work);
	int err, i, tmp, blink_delay = 400;
	bool rerun = false;


	if (priv->mode == NL80211_IFTYPE_UNSPECIFIED)
		return ;

	for (i = 0; i < ARRAY_SIZE(priv->leds); i++)
		if (priv->leds[i].toggled) {
			priv->softled_state |= BIT(i);

			tmp = 70 + 200 / (priv->leds[i].toggled);
			if (tmp < blink_delay)
				blink_delay = tmp;

			if (priv->leds[i].led_dev.brightness == LED_OFF)
				rerun = true;

			priv->leds[i].toggled =
				!!priv->leds[i].led_dev.brightness;
		} else
			priv->softled_state &= ~BIT(i);

	err = p54_set_leds(priv);
	if (err && net_ratelimit())
		wiphy_err(priv->hw->wiphy,
			  "failed to update LEDs (%d).\n", err);

	if (rerun)
		ieee80211_queue_delayed_work(priv->hw, &priv->led_work,
			msecs_to_jiffies(blink_delay));
}
