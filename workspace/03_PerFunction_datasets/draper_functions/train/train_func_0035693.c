axp20x_i2c_remove(struct i2c_client *i2c)
{
	struct axp20x_dev *axp20x = i2c_get_clientdata(i2c);

	if (axp20x == axp20x_pm_power_off) {
		axp20x_pm_power_off = NULL;
		pm_power_off = NULL;
	}

	mfd_remove_devices(axp20x->dev);
	regmap_del_irq_chip(axp20x->i2c_client->irq, axp20x->regmap_irqc);

	return 0;
}
