dw_wdt_drv_probe(struct platform_device *pdev)
{
	int ret;
	struct resource *mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	dw_wdt.regs = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(dw_wdt.regs))
		return PTR_ERR(dw_wdt.regs);

	dw_wdt.clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(dw_wdt.clk))
		return PTR_ERR(dw_wdt.clk);

	ret = clk_prepare_enable(dw_wdt.clk);
	if (ret)
		return ret;

	ret = misc_register(&dw_wdt_miscdev);
	if (ret)
		goto out_disable_clk;

	dw_wdt.restart_handler.notifier_call = dw_wdt_restart_handle;
	dw_wdt.restart_handler.priority = 128;
	ret = register_restart_handler(&dw_wdt.restart_handler);
	if (ret)
		pr_warn("cannot register restart handler\n");

	dw_wdt_set_next_heartbeat();
	setup_timer(&dw_wdt.timer, dw_wdt_ping, 0);
	mod_timer(&dw_wdt.timer, jiffies + WDT_TIMEOUT);

	return 0;

out_disable_clk:
	clk_disable_unprepare(dw_wdt.clk);

	return ret;
}
