as3711_regulator_probe(struct platform_device *pdev)
{
	struct as3711_regulator_pdata *pdata = dev_get_platdata(&pdev->dev);
	struct as3711 *as3711 = dev_get_drvdata(pdev->dev.parent);
	struct regulator_config config = {.dev = &pdev->dev,};
	struct as3711_regulator *reg = NULL;
	struct as3711_regulator *regs;
	struct device_node *of_node[AS3711_REGULATOR_NUM] = {};
	struct regulator_dev *rdev;
	struct as3711_regulator_info *ri;
	int ret;
	int id;

	if (!pdata) {
		dev_err(&pdev->dev, "No platform data...\n");
		return -ENODEV;
	}

	if (pdev->dev.parent->of_node) {
		ret = as3711_regulator_parse_dt(&pdev->dev, of_node, AS3711_REGULATOR_NUM);
		if (ret < 0) {
			dev_err(&pdev->dev, "DT parsing failed: %d\n", ret);
			return ret;
		}
	}

	regs = devm_kzalloc(&pdev->dev, AS3711_REGULATOR_NUM *
			sizeof(struct as3711_regulator), GFP_KERNEL);
	if (!regs)
		return -ENOMEM;

	for (id = 0, ri = as3711_reg_info; id < AS3711_REGULATOR_NUM; ++id, ri++) {
		reg = &regs[id];
		reg->reg_info = ri;

		config.init_data = pdata->init_data[id];
		config.driver_data = reg;
		config.regmap = as3711->regmap;
		config.of_node = of_node[id];

		rdev = devm_regulator_register(&pdev->dev, &ri->desc, &config);
		if (IS_ERR(rdev)) {
			dev_err(&pdev->dev, "Failed to register regulator %s\n",
				ri->desc.name);
			return PTR_ERR(rdev);
		}
	}
	platform_set_drvdata(pdev, regs);
	return 0;
}
