wm8400_dcdc_set_mode(struct regulator_dev *dev, unsigned int mode)
{
	struct wm8400 *wm8400 = rdev_get_drvdata(dev);
	int offset = (rdev_get_id(dev) - WM8400_DCDC1) * 2;
	int ret;

	switch (mode) {
	case REGULATOR_MODE_FAST:

		ret = wm8400_set_bits(wm8400, WM8400_DCDC1_CONTROL_2 + offset,
				      WM8400_DC1_FRC_PWM, WM8400_DC1_FRC_PWM);
		if (ret != 0)
			return ret;

		return wm8400_set_bits(wm8400, WM8400_DCDC1_CONTROL_1 + offset,
				       WM8400_DC1_ACTIVE | WM8400_DC1_SLEEP,
				       WM8400_DC1_ACTIVE);

	case REGULATOR_MODE_NORMAL:

		ret = wm8400_set_bits(wm8400, WM8400_DCDC1_CONTROL_2 + offset,
				      WM8400_DC1_FRC_PWM, 0);
		if (ret != 0)
			return ret;

		return wm8400_set_bits(wm8400, WM8400_DCDC1_CONTROL_1 + offset,
				       WM8400_DC1_ACTIVE | WM8400_DC1_SLEEP,
				       WM8400_DC1_ACTIVE);

	case REGULATOR_MODE_IDLE:

		return wm8400_set_bits(wm8400, WM8400_DCDC1_CONTROL_1 + offset,
				       WM8400_DC1_ACTIVE | WM8400_DC1_SLEEP, 0);
	default:
		return -EINVAL;
	}
}
