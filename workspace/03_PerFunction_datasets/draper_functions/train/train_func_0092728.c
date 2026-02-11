da9211_buck_set_mode(struct regulator_dev *rdev,
					unsigned int mode)
{
	int id = rdev_get_id(rdev);
	struct da9211 *chip = rdev_get_drvdata(rdev);
	int val = 0;

	switch (mode) {
	case REGULATOR_MODE_FAST:
		val = DA9211_BUCK_MODE_SYNC;
		break;
	case REGULATOR_MODE_NORMAL:
		val = DA9211_BUCK_MODE_AUTO;
		break;
	case REGULATOR_MODE_STANDBY:
		val = DA9211_BUCK_MODE_SLEEP;
		break;
	}

	return regmap_update_bits(chip->regmap, DA9211_REG_BUCKA_CONF+id,
					0x03, val);
}
