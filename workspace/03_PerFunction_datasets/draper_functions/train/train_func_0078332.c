ux500_of_probe(struct platform_device *pdev, struct device_node *np)
{
	struct musb_hdrc_platform_data *pdata;
	const char *mode;
	int strlen;

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return NULL;

	mode = of_get_property(np, "dr_mode", &strlen);
	if (!mode) {
		dev_err(&pdev->dev, "No 'dr_mode' property found\n");
		return NULL;
	}

	if (strlen > 0) {
		if (!strcmp(mode, "host"))
			pdata->mode = MUSB_HOST;
		if (!strcmp(mode, "otg"))
			pdata->mode = MUSB_OTG;
		if (!strcmp(mode, "peripheral"))
			pdata->mode = MUSB_PERIPHERAL;
	}

	return pdata;
}
