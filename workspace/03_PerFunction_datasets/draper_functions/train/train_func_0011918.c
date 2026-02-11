w1_gpio_probe_dt(struct platform_device *pdev)
{
	struct w1_gpio_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct device_node *np = pdev->dev.of_node;
	int gpio;

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	if (of_get_property(np, "linux,open-drain", NULL))
		pdata->is_open_drain = 1;

	gpio = of_get_gpio(np, 0);
	if (gpio < 0) {
		if (gpio != -EPROBE_DEFER)
			dev_err(&pdev->dev,
					"Failed to parse gpio property for data pin (%d)\n",
					gpio);

		return gpio;
	}
	pdata->pin = gpio;

	gpio = of_get_gpio(np, 1);
	if (gpio == -EPROBE_DEFER)
		return gpio;

	pdata->ext_pullup_enable_pin = gpio;

	pdev->dev.platform_data = pdata;

	return 0;
}
