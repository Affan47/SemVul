max8997_resume(struct device *dev)
{
	struct i2c_client *i2c = container_of(dev, struct i2c_client, dev);
	struct max8997_dev *max8997 = i2c_get_clientdata(i2c);

	if (device_may_wakeup(dev))
		irq_set_irq_wake(max8997->irq, 0);
	return max8997_irq_resume(max8997);
}
