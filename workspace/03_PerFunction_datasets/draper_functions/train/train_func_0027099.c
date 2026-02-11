tps62360_dcdc_get_voltage_sel(struct regulator_dev *dev)
{
	struct tps62360_chip *tps = rdev_get_drvdata(dev);
	int vsel;
	unsigned int data;
	int ret;

	ret = regmap_read(tps->regmap, REG_VSET0 + tps->curr_vset_id, &data);
	if (ret < 0) {
		dev_err(tps->dev, "%s(): register %d read failed with err %d\n",
			__func__, REG_VSET0 + tps->curr_vset_id, ret);
		return ret;
	}
	vsel = (int)data & tps->voltage_reg_mask;
	return vsel;
}
