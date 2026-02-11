wm8350_device_exit(struct wm8350 *wm8350)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(wm8350->pmic.led); i++)
		platform_device_unregister(wm8350->pmic.led[i].pdev);

	for (i = 0; i < ARRAY_SIZE(wm8350->pmic.pdev); i++)
		platform_device_unregister(wm8350->pmic.pdev[i]);

	platform_device_unregister(wm8350->wdt.pdev);
	platform_device_unregister(wm8350->rtc.pdev);
	platform_device_unregister(wm8350->power.pdev);
	platform_device_unregister(wm8350->hwmon.pdev);
	platform_device_unregister(wm8350->gpio.pdev);
	platform_device_unregister(wm8350->codec.pdev);

	if (wm8350->irq_base)
		free_irq(wm8350->irq_base + WM8350_IRQ_AUXADC_DATARDY, wm8350);

	wm8350_irq_exit(wm8350);
}
