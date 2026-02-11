bcm590xx_parse_dt_reg_data(
		struct platform_device *pdev,
		struct of_regulator_match **bcm590xx_reg_matches)
{
	struct bcm590xx_board *data;
	struct device_node *np = pdev->dev.parent->of_node;
	struct device_node *regulators;
	struct of_regulator_match *matches = bcm590xx_matches;
	int count = ARRAY_SIZE(bcm590xx_matches);
	int idx = 0;
	int ret;

	if (!np) {
		dev_err(&pdev->dev, "of node not found\n");
		return NULL;
	}

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return NULL;

	np = of_node_get(np);
	regulators = of_get_child_by_name(np, "regulators");
	if (!regulators) {
		dev_warn(&pdev->dev, "regulator node not found\n");
		return NULL;
	}

	ret = of_regulator_match(&pdev->dev, regulators, matches, count);
	of_node_put(regulators);
	if (ret < 0) {
		dev_err(&pdev->dev, "Error parsing regulator init data: %d\n",
			ret);
		return NULL;
	}

	*bcm590xx_reg_matches = matches;

	for (idx = 0; idx < count; idx++) {
		if (!matches[idx].init_data || !matches[idx].of_node)
			continue;

		data->bcm590xx_pmu_init_data[idx] = matches[idx].init_data;
	}

	return data;
}
