fan53555_set_ramp(struct regulator_dev *rdev, int ramp)
{
	struct fan53555_device_info *di = rdev_get_drvdata(rdev);
	int regval = -1, i;

	for (i = 0; i < ARRAY_SIZE(slew_rates); i++) {
		if (ramp <= slew_rates[i])
			regval = i;
		else
			break;
	}

	if (regval < 0) {
		dev_err(di->dev, "unsupported ramp value %d\n", ramp);
		return -EINVAL;
	}

	return regmap_update_bits(di->regmap, FAN53555_CONTROL,
				  CTL_SLEW_MASK, regval << CTL_SLEW_SHIFT);
}
