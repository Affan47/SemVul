i2c_put_adapter(struct i2c_adapter *adap)
{
	if (!adap)
		return;

	put_device(&adap->dev);
	module_put(adap->owner);
}
