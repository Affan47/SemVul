spmi_regulator_common_get_mode(struct regulator_dev *rdev)
{
	struct spmi_regulator *vreg = rdev_get_drvdata(rdev);
	u8 reg;

	spmi_vreg_read(vreg, SPMI_COMMON_REG_MODE, &reg, 1);

	if (reg & SPMI_COMMON_MODE_HPM_MASK)
		return REGULATOR_MODE_NORMAL;

	if (reg & SPMI_COMMON_MODE_AUTO_MASK)
		return REGULATOR_MODE_FAST;

	return REGULATOR_MODE_IDLE;
}
