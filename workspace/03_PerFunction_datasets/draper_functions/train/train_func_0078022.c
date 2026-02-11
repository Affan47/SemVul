rcar_pwm_probe(struct platform_device *pdev)
{
	struct rcar_pwm_chip *rcar_pwm;
	struct resource *res;
	int ret;

	rcar_pwm = devm_kzalloc(&pdev->dev, sizeof(*rcar_pwm), GFP_KERNEL);
	if (rcar_pwm == NULL)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rcar_pwm->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(rcar_pwm->base))
		return PTR_ERR(rcar_pwm->base);

	rcar_pwm->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(rcar_pwm->clk)) {
		dev_err(&pdev->dev, "cannot get clock\n");
		return PTR_ERR(rcar_pwm->clk);
	}

	platform_set_drvdata(pdev, rcar_pwm);

	rcar_pwm->chip.dev = &pdev->dev;
	rcar_pwm->chip.ops = &rcar_pwm_ops;
	rcar_pwm->chip.base = -1;
	rcar_pwm->chip.npwm = 1;

	ret = pwmchip_add(&rcar_pwm->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to register PWM chip: %d\n", ret);
		return ret;
	}

	pm_runtime_enable(&pdev->dev);

	return 0;
}
