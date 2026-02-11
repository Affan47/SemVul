ltc4222_get_value(struct device *dev, u8 reg)
{
	struct regmap *regmap = dev_get_drvdata(dev);
	unsigned int val;
	u8 buf[2];
	int ret;

	ret = regmap_bulk_read(regmap, reg, buf, 2);
	if (ret < 0)
		return ret;

	val = ((buf[0] << 8) + buf[1]) >> 6;

	switch (reg) {
	case LTC4222_ADIN1:
	case LTC4222_ADIN2:

		val = DIV_ROUND_CLOSEST(val * 5, 4);
		break;
	case LTC4222_SOURCE1:
	case LTC4222_SOURCE2:

		val = DIV_ROUND_CLOSEST(val * 125, 4);
		break;
	case LTC4222_SENSE1:
	case LTC4222_SENSE2:


		val = DIV_ROUND_CLOSEST(val * 125, 2);
		break;
	default:
		return -EINVAL;
	}
	return val;
}
