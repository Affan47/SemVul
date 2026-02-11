ad7780_set_mode(struct ad_sigma_delta *sigma_delta,
			   enum ad_sigma_delta_mode mode)
{
	struct ad7780_state *st = ad_sigma_delta_to_ad7780(sigma_delta);
	unsigned val;

	switch (mode) {
	case AD_SD_MODE_SINGLE:
	case AD_SD_MODE_CONTINUOUS:
		val = 1;
		break;
	default:
		val = 0;
		break;
	}

	if (gpio_is_valid(st->powerdown_gpio))
		gpio_set_value(st->powerdown_gpio, val);

	return 0;
}
