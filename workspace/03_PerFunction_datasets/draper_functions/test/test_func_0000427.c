tps80031_reg_enable(struct regulator_dev *rdev)
{
	struct tps80031_regulator *ri = rdev_get_drvdata(rdev);
	struct device *parent = to_tps80031_dev(rdev);
	int ret;

	if (ri->ext_ctrl_flag & TPS80031_EXT_PWR_REQ)
		return 0;

	ret = tps80031_update(parent, TPS80031_SLAVE_ID1, ri->rinfo->state_reg,
			TPS80031_STATE_ON, TPS80031_STATE_MASK);
	if (ret < 0) {
		dev_err(&rdev->dev, "Reg 0x%02x update failed, err = %d\n",
			ri->rinfo->state_reg, ret);
		return ret;
	}
	return ret;
}
