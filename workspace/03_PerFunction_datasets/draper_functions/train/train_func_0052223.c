ltc3589_set_suspend_voltage(struct regulator_dev *rdev, int uV)
{
	struct ltc3589 *ltc3589 = rdev_get_drvdata(rdev);
	int sel;

	sel = regulator_map_voltage_linear(rdev, uV, uV);
	if (sel < 0)
		return sel;


	return regmap_update_bits(ltc3589->regmap, rdev->desc->vsel_reg + 1,
				  rdev->desc->vsel_mask, sel);
}
