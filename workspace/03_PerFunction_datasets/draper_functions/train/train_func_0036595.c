lpc18xx_gpio_probe(struct platform_device *pdev)
{
	struct lpc18xx_gpio_chip *gc;
	struct resource *res;
	int ret;

	gc = devm_kzalloc(&pdev->dev, sizeof(*gc), GFP_KERNEL);
	if (!gc)
		return -ENOMEM;

	gc->gpio = lpc18xx_chip;
	platform_set_drvdata(pdev, gc);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	gc->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(gc->base))
		return PTR_ERR(gc->base);

	gc->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(gc->clk)) {
		dev_err(&pdev->dev, "input clock not found\n");
		return PTR_ERR(gc->clk);
	}

	ret = clk_prepare_enable(gc->clk);
	if (ret) {
		dev_err(&pdev->dev, "unable to enable clock\n");
		return ret;
	}

	spin_lock_init(&gc->lock);

	gc->gpio.dev = &pdev->dev;

	ret = gpiochip_add(&gc->gpio);
	if (ret) {
		dev_err(&pdev->dev, "failed to add gpio chip\n");
		clk_disable_unprepare(gc->clk);
		return ret;
	}

	return 0;
}
