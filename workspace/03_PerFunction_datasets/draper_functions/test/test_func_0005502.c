max8997_set_current_limit(struct regulator_dev *rdev,
				     int min_uA, int max_uA)
{
	unsigned dummy;
	int rid = rdev_get_id(rdev);

	if (rid != MAX8997_CHARGER && rid != MAX8997_CHARGER_TOPOFF)
		return -EINVAL;


	return max8997_set_voltage_ldobuck(rdev, min_uA, max_uA, &dummy);
}
