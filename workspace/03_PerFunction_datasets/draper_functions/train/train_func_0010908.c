samsung_keypad_runtime_suspend(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct samsung_keypad *keypad = platform_get_drvdata(pdev);
	unsigned int val;
	int error;

	if (keypad->stopped)
		return 0;


	error = enable_irq_wake(keypad->irq);
	if (!error)
		keypad->wake_enabled = true;

	val = readl(keypad->base + SAMSUNG_KEYIFCON);
	val |= SAMSUNG_KEYIFCON_WAKEUPEN;
	writel(val, keypad->base + SAMSUNG_KEYIFCON);

	clk_disable(keypad->clk);

	return 0;
}
