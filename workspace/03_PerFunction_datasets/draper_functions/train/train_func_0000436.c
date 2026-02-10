syscon_poweroff_probe(struct platform_device *pdev)
{
	char symname[KSYM_NAME_LEN];

	map = syscon_regmap_lookup_by_phandle(pdev->dev.of_node, "regmap");
	if (IS_ERR(map)) {
		dev_err(&pdev->dev, "unable to get syscon");
		return PTR_ERR(map);
	}

	if (of_property_read_u32(pdev->dev.of_node, "offset", &offset)) {
		dev_err(&pdev->dev, "unable to read 'offset'");
		return -EINVAL;
	}

	if (of_property_read_u32(pdev->dev.of_node, "mask", &mask)) {
		dev_err(&pdev->dev, "unable to read 'mask'");
		return -EINVAL;
	}

	if (pm_power_off) {
		lookup_symbol_name((ulong)pm_power_off, symname);
		dev_err(&pdev->dev,
		"pm_power_off already claimed %p %s",
		pm_power_off, symname);
		return -EBUSY;
	}

	pm_power_off = syscon_poweroff;

	return 0;
}
