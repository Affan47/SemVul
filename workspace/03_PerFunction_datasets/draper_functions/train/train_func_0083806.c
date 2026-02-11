pwm_regulator_probe(struct platform_device *pdev)
{
	const struct regulator_init_data *init_data;
	struct pwm_regulator_data *drvdata;
	struct regulator_dev *regulator;
	struct regulator_config config = { };
	struct device_node *np = pdev->dev.of_node;
	int ret;

	if (!np) {
		dev_err(&pdev->dev, "Device Tree node missing\n");
		return -EINVAL;
	}

	drvdata = devm_kzalloc(&pdev->dev, sizeof(*drvdata), GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;

	if (of_find_property(np, "voltage-table", NULL))
		ret = pwm_regulator_init_table(pdev, drvdata);
	else
		ret = pwm_regulator_init_continuous(pdev, drvdata);
	if (ret)
		return ret;

	init_data = of_get_regulator_init_data(&pdev->dev, np,
					       &pwm_regulator_desc);
	if (!init_data)
		return -ENOMEM;

	config.of_node = np;
	config.dev = &pdev->dev;
	config.driver_data = drvdata;
	config.init_data = init_data;

	drvdata->pwm = devm_pwm_get(&pdev->dev, NULL);
	if (IS_ERR(drvdata->pwm)) {
		dev_err(&pdev->dev, "Failed to get PWM\n");
		return PTR_ERR(drvdata->pwm);
	}

	regulator = devm_regulator_register(&pdev->dev,
					    &pwm_regulator_desc, &config);
	if (IS_ERR(regulator)) {
		dev_err(&pdev->dev, "Failed to register regulator %s\n",
			pwm_regulator_desc.name);
		return PTR_ERR(regulator);
	}

	return 0;
}
