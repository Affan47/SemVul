isl29028_set_als_ir_mode(struct isl29028_chip *chip,
	enum als_ir_mode mode)
{
	int ret = 0;

	switch (mode) {
	case MODE_ALS:
		ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
			CONFIGURE_ALS_IR_MODE_MASK, CONFIGURE_ALS_IR_MODE_ALS);
		if (ret < 0)
			return ret;

		ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
			CONFIGURE_ALS_RANGE_MASK, CONFIGURE_ALS_RANGE_HIGH_LUX);
		break;

	case MODE_IR:
		ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
			CONFIGURE_ALS_IR_MODE_MASK, CONFIGURE_ALS_IR_MODE_IR);
		break;

	case MODE_NONE:
		return regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
			CONFIGURE_ALS_EN_MASK, CONFIGURE_ALS_DIS);
	}

	if (ret < 0)
		return ret;


	ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
			CONFIGURE_ALS_EN_MASK, CONFIGURE_ALS_EN);
	if (ret < 0)
		return ret;


	mdelay(CONVERSION_TIME_MS);
	return 0;
}
