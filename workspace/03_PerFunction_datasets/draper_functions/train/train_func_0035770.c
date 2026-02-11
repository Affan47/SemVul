lpc18xx_scu_probe(struct platform_device *pdev)
{
	struct lpc18xx_scu_data *scu;
	struct resource *res;
	int ret;

	scu = devm_kzalloc(&pdev->dev, sizeof(*scu), GFP_KERNEL);
	if (!scu)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	scu->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(scu->base))
		return PTR_ERR(scu->base);

	scu->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(scu->clk)) {
		dev_err(&pdev->dev, "Input clock not found.\n");
		return PTR_ERR(scu->clk);
	}

	ret = lpc18xx_create_group_func_map(&pdev->dev, scu);
	if (ret) {
		dev_err(&pdev->dev, "Unable to create group func map.\n");
		return ret;
	}

	ret = clk_prepare_enable(scu->clk);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable clock.\n");
		return ret;
	}

	platform_set_drvdata(pdev, scu);

	scu->pctl = pinctrl_register(&lpc18xx_scu_desc, &pdev->dev, scu);
	if (IS_ERR(scu->pctl)) {
		dev_err(&pdev->dev, "Could not register pinctrl driver\n");
		clk_disable_unprepare(scu->clk);
		return PTR_ERR(scu->pctl);
	}

	return 0;
}
