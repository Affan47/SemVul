tps65912_get_voltage_sel(struct regulator_dev *dev)
{
	struct tps65912_reg *pmic = rdev_get_drvdata(dev);
	struct tps65912 *mfd = pmic->mfd;
	int id = rdev_get_id(dev);
	int reg, vsel;

	reg = tps65912_get_sel_register(pmic, id);
	if (reg < 0)
		return reg;

	vsel = tps65912_reg_read(mfd, reg);
	vsel &= 0x3F;

	return vsel;
}
