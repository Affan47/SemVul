lp8788_buck_get_mode(struct regulator_dev *rdev)
{
	struct lp8788_buck *buck = rdev_get_drvdata(rdev);
	enum lp8788_buck_id id = rdev_get_id(rdev);
	u8 val;
	int ret;

	ret = lp8788_read_byte(buck->lp, LP8788_BUCK_PWM, &val);
	if (ret)
		return ret;

	return val & BUCK_FPWM_MASK(id) ?
				REGULATOR_MODE_FAST : REGULATOR_MODE_NORMAL;
}
