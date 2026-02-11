da9063_wdt_set_timeout(struct watchdog_device *wdd,
				  unsigned int timeout)
{
	struct da9063_watchdog *wdt = watchdog_get_drvdata(wdd);
	unsigned int selector;
	int ret;

	selector = da9063_wdt_timeout_to_sel(timeout);
	ret = _da9063_wdt_set_timeout(wdt->da9063, selector);
	if (ret)
		dev_err(wdt->da9063->dev, "Failed to set watchdog timeout (err = %d)\n",
			ret);
	else
		wdd->timeout = wdt_timeout[selector];

	return ret;
}
