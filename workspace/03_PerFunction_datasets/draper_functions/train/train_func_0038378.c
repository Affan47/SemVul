show_output(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct lm3533 *lm3533 = dev_get_drvdata(dev);
	struct lm3533_device_attribute *lattr = to_lm3533_dev_attr(attr);
	int id = lattr->u.output.id;
	u8 reg;
	u8 val;
	u8 mask;
	int shift;
	int ret;

	if (lattr->type == LM3533_ATTR_TYPE_BACKLIGHT) {
		reg = LM3533_REG_OUTPUT_CONF1;
		shift = id - 1;
		mask = LM3533_BL_ID_MASK << shift;
	} else {
		if (id < 4) {
			reg = LM3533_REG_OUTPUT_CONF1;
			shift = 2 * id;
		} else {
			reg = LM3533_REG_OUTPUT_CONF2;
			shift = 2 * (id - 4);
		}
		mask = LM3533_LED_ID_MASK << shift;
	}

	ret = lm3533_read(lm3533, reg, &val);
	if (ret)
		return ret;

	val = (val & mask) >> shift;

	return scnprintf(buf, PAGE_SIZE, "%u\n", val);
}
