axp20x_show_ext_attr(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	struct axp20x_pek *axp20x_pek = dev_get_drvdata(dev);
	struct axp20x_pek_ext_attr *axp20x_ea = get_axp_ext_attr(attr);
	unsigned int val;
	int ret, i;

	ret = regmap_read(axp20x_pek->axp20x->regmap, AXP20X_PEK_KEY, &val);
	if (ret != 0)
		return ret;

	val &= axp20x_ea->mask;
	val >>= ffs(axp20x_ea->mask) - 1;

	for (i = 0; i < 4; i++)
		if (val == axp20x_ea->p_time[i].idx)
			val = axp20x_ea->p_time[i].time;

	return sprintf(buf, "%u\n", val);
}
