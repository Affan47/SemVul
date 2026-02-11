arizona_thermal_warn(int irq, void *data)
{
	struct arizona *arizona = data;
	unsigned int val;
	int ret;

	ret = regmap_read(arizona->regmap, ARIZONA_INTERRUPT_RAW_STATUS_3,
			  &val);
	if (ret != 0) {
		dev_err(arizona->dev, "Failed to read thermal status: %d\n",
			ret);
	} else if (val & ARIZONA_SPK_OVERHEAT_WARN_STS) {
		dev_crit(arizona->dev, "Thermal warning\n");
	}

	return IRQ_HANDLED;
}
