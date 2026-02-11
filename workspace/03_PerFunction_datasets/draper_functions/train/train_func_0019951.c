lm3533_led_pattern_enable(struct lm3533_led *led, int enable)
{
	u8 mask;
	u8 val;
	int pattern;
	int state;
	int ret = 0;

	dev_dbg(led->cdev.dev, "%s - %d\n", __func__, enable);

	mutex_lock(&led->mutex);

	state = test_bit(LM3533_LED_FLAG_PATTERN_ENABLE, &led->flags);
	if ((enable && state) || (!enable && !state))
		goto out;

	pattern = lm3533_led_get_pattern(led);
	mask = 1 << (2 * pattern);

	if (enable)
		val = mask;
	else
		val = 0;

	ret = lm3533_update(led->lm3533, LM3533_REG_PATTERN_ENABLE, val, mask);
	if (ret) {
		dev_err(led->cdev.dev, "failed to enable pattern %d (%d)\n",
							pattern, enable);
		goto out;
	}

	__change_bit(LM3533_LED_FLAG_PATTERN_ENABLE, &led->flags);
out:
	mutex_unlock(&led->mutex);

	return ret;
}
