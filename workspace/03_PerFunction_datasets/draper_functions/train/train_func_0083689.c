sky81452_bl_parse_dt(
							struct device *dev)
{
	struct device_node *np = of_node_get(dev->of_node);
	struct sky81452_bl_platform_data *pdata;
	int num_entry;
	unsigned int sources[6];
	int ret;

	if (!np) {
		dev_err(dev, "backlight node not found.\n");
		return ERR_PTR(-ENODATA);
	}

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata) {
		of_node_put(np);
		return ERR_PTR(-ENOMEM);
	}

	of_property_read_string(np, "name", &pdata->name);
	pdata->ignore_pwm = of_property_read_bool(np, "skyworks,ignore-pwm");
	pdata->dpwm_mode = of_property_read_bool(np, "skyworks,dpwm-mode");
	pdata->phase_shift = of_property_read_bool(np, "skyworks,phase-shift");
	pdata->gpio_enable = of_get_gpio(np, 0);

	ret = of_property_count_u32_elems(np, "led-sources");
	if (ret < 0) {
		pdata->enable = SKY81452_EN >> CTZ(SKY81452_EN);
	} else {
		num_entry = ret;
		if (num_entry > 6)
			num_entry = 6;

		ret = of_property_read_u32_array(np, "led-sources", sources,
					num_entry);
		if (ret < 0) {
			dev_err(dev, "led-sources node is invalid.\n");
			return ERR_PTR(-EINVAL);
		}

		pdata->enable = 0;
		while (--num_entry)
			pdata->enable |= (1 << sources[num_entry]);
	}

	ret = of_property_read_u32(np,
			"skyworks,short-detection-threshold-volt",
			&pdata->short_detection_threshold);
	if (ret < 0)
		pdata->short_detection_threshold = 7;

	ret = of_property_read_u32(np, "skyworks,current-limit-mA",
			&pdata->boost_current_limit);
	if (ret < 0)
		pdata->boost_current_limit = 2750;

	of_node_put(np);
	return pdata;
}
