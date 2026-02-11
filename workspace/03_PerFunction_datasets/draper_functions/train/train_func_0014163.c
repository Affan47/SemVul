omap4_keypad_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct omap4_keypad *keypad_data = platform_get_drvdata(pdev);

	if (device_may_wakeup(&pdev->dev) && keypad_data->irq_wake_enabled) {
		disable_irq_wake(keypad_data->irq);
		keypad_data->irq_wake_enabled = false;
	}

	return 0;
}
