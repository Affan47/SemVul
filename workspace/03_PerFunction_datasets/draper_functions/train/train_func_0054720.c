arizona_of_get_core_pdata(struct arizona *arizona)
{
	struct arizona_pdata *pdata = &arizona->pdata;
	struct property *prop;
	const __be32 *cur;
	u32 val;
	int ret, i;
	int count = 0;

	pdata->reset = arizona_of_get_named_gpio(arizona, "wlf,reset", true);

	ret = of_property_read_u32_array(arizona->dev->of_node,
					 "wlf,gpio-defaults",
					 pdata->gpio_defaults,
					 ARRAY_SIZE(pdata->gpio_defaults));
	if (ret >= 0) {


		for (i = 0; i < ARRAY_SIZE(pdata->gpio_defaults); i++) {
			if (pdata->gpio_defaults[i] > 0xffff)
				pdata->gpio_defaults[i] = 0;
			else if (pdata->gpio_defaults[i] == 0)
				pdata->gpio_defaults[i] = 0x10000;
		}
	} else {
		dev_err(arizona->dev, "Failed to parse GPIO defaults: %d\n",
			ret);
	}

	of_property_for_each_u32(arizona->dev->of_node, "wlf,inmode", prop,
				 cur, val) {
		if (count == ARRAY_SIZE(pdata->inmode))
			break;

		pdata->inmode[count] = val;
		count++;
	}

	count = 0;
	of_property_for_each_u32(arizona->dev->of_node, "wlf,dmic-ref", prop,
				 cur, val) {
		if (count == ARRAY_SIZE(pdata->dmic_ref))
			break;

		pdata->dmic_ref[count] = val;
		count++;
	}

	return 0;
}
