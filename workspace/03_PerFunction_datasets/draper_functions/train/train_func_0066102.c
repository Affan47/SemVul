flctl_parse_dt(struct device *dev)
{
	const struct of_device_id *match;
	struct flctl_soc_config *config;
	struct sh_flctl_platform_data *pdata;
	struct device_node *dn = dev->of_node;
	int ret;

	match = of_match_device(of_flctl_match, dev);
	if (match)
		config = (struct flctl_soc_config *)match->data;
	else {
		dev_err(dev, "%s: no OF configuration attached\n", __func__);
		return NULL;
	}

	pdata = devm_kzalloc(dev, sizeof(struct sh_flctl_platform_data),
								GFP_KERNEL);
	if (!pdata)
		return NULL;


	pdata->flcmncr_val = config->flcmncr_val;
	pdata->has_hwecc = config->has_hwecc;
	pdata->use_holden = config->use_holden;


	ret = of_get_nand_bus_width(dn);
	if (ret == 16)
		pdata->flcmncr_val |= SEL_16BIT;
	else if (ret != 8) {
		dev_err(dev, "%s: invalid bus width\n", __func__);
		return NULL;
	}

	return pdata;
}
