s2mps14_regulator_enable(struct regulator_dev *rdev)
{
	struct s2mps11_info *s2mps11 = rdev_get_drvdata(rdev);
	unsigned int val;

	switch (s2mps11->dev_type) {
	case S2MPS13X:
	case S2MPS14X:
		if (test_bit(rdev_get_id(rdev), s2mps11->suspend_state))
			val = S2MPS14_ENABLE_SUSPEND;
		else if (gpio_is_valid(s2mps11->ext_control_gpio[rdev_get_id(rdev)]))
			val = S2MPS14_ENABLE_EXT_CONTROL;
		else
			val = rdev->desc->enable_mask;
		break;
	case S2MPU02:
		if (test_bit(rdev_get_id(rdev), s2mps11->suspend_state))
			val = S2MPU02_ENABLE_SUSPEND;
		else
			val = rdev->desc->enable_mask;
		break;
	default:
		return -EINVAL;
	}

	return regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
			rdev->desc->enable_mask, val);
}
