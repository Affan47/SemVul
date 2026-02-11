regulator_haptic_probe(struct platform_device *pdev)
{
	const struct regulator_haptic_data *pdata = dev_get_platdata(&pdev->dev);
	struct regulator_haptic *haptic;
	struct input_dev *input_dev;
	int error;

	haptic = devm_kzalloc(&pdev->dev, sizeof(*haptic), GFP_KERNEL);
	if (!haptic)
		return -ENOMEM;

	platform_set_drvdata(pdev, haptic);
	haptic->dev = &pdev->dev;
	mutex_init(&haptic->mutex);
	INIT_WORK(&haptic->work, regulator_haptic_work);

	if (pdata) {
		haptic->max_volt = pdata->max_volt;
		haptic->min_volt = pdata->min_volt;
	} else if (IS_ENABLED(CONFIG_OF)) {
		error = regulator_haptic_parse_dt(&pdev->dev, haptic);
		if (error)
			return error;
	} else {
		dev_err(&pdev->dev, "Missing platform data\n");
		return -EINVAL;
	}

	haptic->regulator = devm_regulator_get_exclusive(&pdev->dev, "haptic");
	if (IS_ERR(haptic->regulator)) {
		dev_err(&pdev->dev, "failed to get regulator\n");
		return PTR_ERR(haptic->regulator);
	}

	input_dev = devm_input_allocate_device(&pdev->dev);
	if (!input_dev)
		return	-ENOMEM;

	haptic->input_dev = input_dev;
	haptic->input_dev->name = "regulator-haptic";
	haptic->input_dev->dev.parent = &pdev->dev;
	haptic->input_dev->close = regulator_haptic_close;
	input_set_drvdata(haptic->input_dev, haptic);
	input_set_capability(haptic->input_dev, EV_FF, FF_RUMBLE);

	error = input_ff_create_memless(input_dev, NULL,
					regulator_haptic_play_effect);
	if (error) {
		dev_err(&pdev->dev, "failed to create force-feedback\n");
		return error;
	}

	error = input_register_device(haptic->input_dev);
	if (error) {
		dev_err(&pdev->dev, "failed to register input device\n");
		return error;
	}

	return 0;
}
