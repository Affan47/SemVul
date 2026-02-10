drms_uA_update(struct regulator_dev *rdev)
{
	struct regulator *sibling;
	int current_uA = 0, output_uV, input_uV, err;
	unsigned int mode;

	lockdep_assert_held_once(&rdev->mutex);


	err = regulator_check_drms(rdev);
	if (err < 0)
		return 0;

	if (!rdev->desc->ops->get_optimum_mode &&
	    !rdev->desc->ops->set_load)
		return 0;

	if (!rdev->desc->ops->set_mode &&
	    !rdev->desc->ops->set_load)
		return -EINVAL;


	output_uV = _regulator_get_voltage(rdev);
	if (output_uV <= 0) {
		rdev_err(rdev, "invalid output voltage found\n");
		return -EINVAL;
	}


	input_uV = 0;
	if (rdev->supply)
		input_uV = regulator_get_voltage(rdev->supply);
	if (input_uV <= 0)
		input_uV = rdev->constraints->input_uV;
	if (input_uV <= 0) {
		rdev_err(rdev, "invalid input voltage found\n");
		return -EINVAL;
	}


	list_for_each_entry(sibling, &rdev->consumer_list, list)
		current_uA += sibling->uA_load;

	current_uA += rdev->constraints->system_load;

	if (rdev->desc->ops->set_load) {

		err = rdev->desc->ops->set_load(rdev, current_uA);
		if (err < 0)
			rdev_err(rdev, "failed to set load %d\n", current_uA);
	} else {

		mode = rdev->desc->ops->get_optimum_mode(rdev, input_uV,
							 output_uV, current_uA);


		err = regulator_mode_constrain(rdev, &mode);
		if (err < 0) {
			rdev_err(rdev, "failed to get optimum mode @ %d uA %d -> %d uV\n",
				 current_uA, input_uV, output_uV);
			return err;
		}

		err = rdev->desc->ops->set_mode(rdev, mode);
		if (err < 0)
			rdev_err(rdev, "failed to set optimum mode %x\n", mode);
	}

	return err;
}
