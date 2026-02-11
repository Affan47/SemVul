retu_remove(struct i2c_client *i2c)
{
	struct retu_dev *rdev = i2c_get_clientdata(i2c);

	if (retu_pm_power_off == rdev) {
		pm_power_off	  = NULL;
		retu_pm_power_off = NULL;
	}
	mfd_remove_devices(rdev->dev);
	regmap_del_irq_chip(i2c->irq, rdev->irq_data);

	return 0;
}
