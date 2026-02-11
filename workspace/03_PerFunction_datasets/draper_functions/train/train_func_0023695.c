max77686_pmic_probe(struct platform_device *pdev)
{
	struct max77686_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	struct max77686_data *max77686;
	int i;
	struct regulator_config config = { };

	dev_dbg(&pdev->dev, "%s\n", __func__);

	max77686 = devm_kzalloc(&pdev->dev, sizeof(struct max77686_data),
				GFP_KERNEL);
	if (!max77686)
		return -ENOMEM;

	config.dev = iodev->dev;
	config.regmap = iodev->regmap;
	config.driver_data = max77686;
	platform_set_drvdata(pdev, max77686);

	for (i = 0; i < MAX77686_REGULATORS; i++) {
		struct regulator_dev *rdev;
		int id = regulators[i].id;

		max77686->opmode[id] = MAX77686_NORMAL;
		rdev = devm_regulator_register(&pdev->dev,
						&regulators[i], &config);
		if (IS_ERR(rdev)) {
			int ret = PTR_ERR(rdev);
			dev_err(&pdev->dev,
				"regulator init failed for %d: %d\n", i, ret);
			return ret;
		}
	}

	return 0;
}
