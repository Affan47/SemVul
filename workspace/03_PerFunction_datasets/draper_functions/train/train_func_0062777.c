mms114_parse_dt(struct device *dev)
{
	struct mms114_platform_data *pdata;
	struct device_node *np = dev->of_node;

	if (!np)
		return NULL;

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata) {
		dev_err(dev, "failed to allocate platform data\n");
		return NULL;
	}

	if (of_property_read_u32(np, "x-size", &pdata->x_size)) {
		dev_err(dev, "failed to get x-size property\n");
		return NULL;
	}

	if (of_property_read_u32(np, "y-size", &pdata->y_size)) {
		dev_err(dev, "failed to get y-size property\n");
		return NULL;
	}

	of_property_read_u32(np, "contact-threshold",
				&pdata->contact_threshold);
	of_property_read_u32(np, "moving-threshold",
				&pdata->moving_threshold);

	if (of_find_property(np, "x-invert", NULL))
		pdata->x_invert = true;
	if (of_find_property(np, "y-invert", NULL))
		pdata->y_invert = true;

	return pdata;
}
