max77693_muic_set_path(struct max77693_muic_info *info,
		u8 val, bool attached)
{
	int ret = 0;
	unsigned int ctrl1, ctrl2 = 0;

	if (attached)
		ctrl1 = val;
	else
		ctrl1 = MAX77693_CONTROL1_SW_OPEN;

	ret = regmap_update_bits(info->max77693->regmap_muic,
			MAX77693_MUIC_REG_CTRL1, COMP_SW_MASK, ctrl1);
	if (ret < 0) {
		dev_err(info->dev, "failed to update MUIC register\n");
		return ret;
	}

	if (attached)
		ctrl2 |= MAX77693_CONTROL2_CPEN_MASK;
	else
		ctrl2 |= MAX77693_CONTROL2_LOWPWR_MASK;

	ret = regmap_update_bits(info->max77693->regmap_muic,
			MAX77693_MUIC_REG_CTRL2,
			MAX77693_CONTROL2_LOWPWR_MASK | MAX77693_CONTROL2_CPEN_MASK,
			ctrl2);
	if (ret < 0) {
		dev_err(info->dev, "failed to update MUIC register\n");
		return ret;
	}

	dev_info(info->dev,
		"CONTROL1 : 0x%02x, CONTROL2 : 0x%02x, state : %s\n",
		ctrl1, ctrl2, attached ? "attached" : "detached");

	return 0;
}
