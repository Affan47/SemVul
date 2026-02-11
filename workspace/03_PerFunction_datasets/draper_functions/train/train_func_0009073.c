max77693_get_strobe_status(struct max77693_led_device *led,
					bool *state)
{
	struct regmap *rmap = led->regmap;
	unsigned int v;
	int ret;

	ret = regmap_read(rmap, MAX77693_LED_REG_FLASH_STATUS, &v);
	if (ret < 0)
		return ret;

	*state = v & FLASH_STATUS_FLASH_ON;

	return ret;
}
