da9063_wdt_probe(struct platform_device *pdev)
{
	int ret;
	struct da9063 *da9063;
	struct da9063_watchdog *wdt;

	if (!pdev->dev.parent)
		return -EINVAL;

	da9063 = dev_get_drvdata(pdev->dev.parent);
	if (!da9063)
		return -EINVAL;

	wdt = devm_kzalloc(&pdev->dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	wdt->da9063 = da9063;

	wdt->wdtdev.info = &da9063_watchdog_info;
	wdt->wdtdev.ops = &da9063_watchdog_ops;
	wdt->wdtdev.min_timeout = DA9063_WDT_MIN_TIMEOUT;
	wdt->wdtdev.max_timeout = DA9063_WDT_MAX_TIMEOUT;
	wdt->wdtdev.timeout = DA9063_WDG_TIMEOUT;
	wdt->wdtdev.parent = &pdev->dev;

	wdt->wdtdev.status = WATCHDOG_NOWAYOUT_INIT_STATUS;

	watchdog_set_drvdata(&wdt->wdtdev, wdt);
	dev_set_drvdata(&pdev->dev, wdt);

	ret = watchdog_register_device(&wdt->wdtdev);
	if (ret)
		return ret;

	wdt->restart_handler.notifier_call = da9063_wdt_restart_handler;
	wdt->restart_handler.priority = 128;
	ret = register_restart_handler(&wdt->restart_handler);
	if (ret)
		dev_err(wdt->da9063->dev,
			"Failed to register restart handler (err = %d)\n", ret);

	return 0;
}
