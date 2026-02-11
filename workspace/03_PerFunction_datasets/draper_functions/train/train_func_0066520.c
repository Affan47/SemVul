set_supply(struct regulator_dev *rdev,
		      struct regulator_dev *supply_rdev)
{
	int err;

	rdev_info(rdev, "supplied by %s\n", rdev_get_name(supply_rdev));

	if (!try_module_get(supply_rdev->owner))
		return -ENODEV;

	rdev->supply = create_regulator(supply_rdev, &rdev->dev, "SUPPLY");
	if (rdev->supply == NULL) {
		err = -ENOMEM;
		return err;
	}
	supply_rdev->open_count++;

	return 0;
}
