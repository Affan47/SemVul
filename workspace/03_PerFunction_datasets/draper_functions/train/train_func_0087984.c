rt5640_parse_dt(struct rt5640_priv *rt5640, struct device_node *np)
{
	rt5640->pdata.in1_diff = of_property_read_bool(np,
					"realtek,in1-differential");
	rt5640->pdata.in2_diff = of_property_read_bool(np,
					"realtek,in2-differential");

	rt5640->pdata.ldo1_en = of_get_named_gpio(np,
					"realtek,ldo1-en-gpios", 0);


	if (!gpio_is_valid(rt5640->pdata.ldo1_en) &&
			(rt5640->pdata.ldo1_en != -ENOENT))
		return rt5640->pdata.ldo1_en;

	return 0;
}
