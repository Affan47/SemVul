max8907_regulator_parse_dt(struct platform_device *pdev)
{
	struct device_node *np, *regulators;
	int ret;

	np = pdev->dev.parent->of_node;
	if (!np)
		return 0;

	regulators = of_get_child_by_name(np, "regulators");
	if (!regulators) {
		dev_err(&pdev->dev, "regulators node not found\n");
		return -EINVAL;
	}

	ret = of_regulator_match(&pdev->dev, regulators, max8907_matches,
				 ARRAY_SIZE(max8907_matches));
	of_node_put(regulators);
	if (ret < 0) {
		dev_err(&pdev->dev, "Error parsing regulator init data: %d\n",
			ret);
		return ret;
	}

	return 0;
}
