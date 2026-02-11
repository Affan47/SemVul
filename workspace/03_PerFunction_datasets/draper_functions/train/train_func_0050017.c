wm8400_reg_read(struct wm8400 *wm8400, u8 reg)
{
	unsigned int val;
	int ret;

	ret = regmap_read(wm8400->regmap, reg, &val);
	if (ret < 0)
		return ret;

	return val;
}
