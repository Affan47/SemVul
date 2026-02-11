setup_regulators(struct lp3972 *lp3972,
	struct lp3972_platform_data *pdata)
{
	int i, err;


	for (i = 0; i < pdata->num_regulators; i++) {
		struct lp3972_regulator_subdev *reg = &pdata->regulators[i];
		struct regulator_config config = { };
		struct regulator_dev *rdev;

		config.dev = lp3972->dev;
		config.init_data = reg->initdata;
		config.driver_data = lp3972;

		rdev = devm_regulator_register(lp3972->dev,
					       &regulators[reg->id], &config);
		if (IS_ERR(rdev)) {
			err = PTR_ERR(rdev);
			dev_err(lp3972->dev, "regulator init failed: %d\n",
				err);
			return err;
		}
	}

	return 0;
}
