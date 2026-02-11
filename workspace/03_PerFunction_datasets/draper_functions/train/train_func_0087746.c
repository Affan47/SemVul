da9062_wdt_update_timeout_register(struct da9062_watchdog *wdt,
					      unsigned int regval)
{
	struct da9062 *chip = wdt->hw;
	int ret;

	ret = da9062_reset_watchdog_timer(wdt);
	if (ret)
		return ret;

	return regmap_update_bits(chip->regmap,
				  DA9062AA_CONTROL_D,
				  DA9062AA_TWDSCALE_MASK,
				  regval);
}
