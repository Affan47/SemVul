da9052_gpio_probe(struct platform_device *pdev)
{
	struct da9052_gpio *gpio;
	struct da9052_pdata *pdata;
	int ret;

	gpio = devm_kzalloc(&pdev->dev, sizeof(*gpio), GFP_KERNEL);
	if (!gpio)
		return -ENOMEM;

	gpio->da9052 = dev_get_drvdata(pdev->dev.parent);
	pdata = dev_get_platdata(gpio->da9052->dev);

	gpio->gp = reference_gp;
	if (pdata && pdata->gpio_base)
		gpio->gp.base = pdata->gpio_base;

	ret = gpiochip_add(&gpio->gp);
	if (ret < 0) {
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, gpio);

	return 0;
}
