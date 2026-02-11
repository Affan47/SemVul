regulator_resolve_supply(struct regulator_dev *rdev)
{
	struct regulator_dev *r;
	struct device *dev = rdev->dev.parent;
	int ret;


	if (!rdev->supply_name)
		return 0;


	if (rdev->supply)
		return 0;

	r = regulator_dev_lookup(dev, rdev->supply_name, &ret);
	if (!r) {
		if (ret == -ENODEV) {


			return 0;
		}


		if (ret == -EPROBE_DEFER)
			return ret;

		if (have_full_constraints()) {
			r = dummy_regulator_rdev;
			get_device(&r->dev);
		} else {
			dev_err(dev, "Failed to resolve %s-supply for %s\n",
				rdev->supply_name, rdev->desc->name);
			return -EPROBE_DEFER;
		}
	}


	ret = regulator_resolve_supply(r);
	if (ret < 0) {
		put_device(&r->dev);
		return ret;
	}

	ret = set_supply(rdev, r);
	if (ret < 0) {
		put_device(&r->dev);
		return ret;
	}


	if (_regulator_is_enabled(rdev) && rdev->supply) {
		ret = regulator_enable(rdev->supply);
		if (ret < 0) {
			_regulator_put(rdev->supply);
			rdev->supply = NULL;
			return ret;
		}
	}

	return 0;
}
