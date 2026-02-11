pm8607_list_voltage(struct regulator_dev *rdev, unsigned index)
{
	struct pm8607_regulator_info *info = rdev_get_drvdata(rdev);
	int ret = -EINVAL;

	if (info->vol_table && (index < rdev->desc->n_voltages)) {
		ret = info->vol_table[index];
		if (info->slope_double)
			ret <<= 1;
	}
	return ret;
}
