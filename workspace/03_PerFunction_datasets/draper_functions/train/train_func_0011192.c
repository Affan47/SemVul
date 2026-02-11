lp8755_buck_get_mode(struct regulator_dev *rdev)
{
	int ret;
	unsigned int regval;
	enum lp8755_bucks id = rdev_get_id(rdev);
	struct lp8755_chip *pchip = rdev_get_drvdata(rdev);

	ret = lp8755_read(pchip, 0x06, &regval);
	if (ret < 0)
		goto err_i2c;


	if (regval & (0x01 << id))
		return REGULATOR_MODE_FAST;

	ret = lp8755_read(pchip, 0x08 + id, &regval);
	if (ret < 0)
		goto err_i2c;


	if (regval & 0x20)
		return REGULATOR_MODE_IDLE;


	return REGULATOR_MODE_NORMAL;

err_i2c:
	dev_err(pchip->dev, "i2c acceess error %s\n", __func__);
	return 0;
}
