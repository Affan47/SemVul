__i2c_bit_add_bus(struct i2c_adapter *adap,
			     int (*add_adapter)(struct i2c_adapter *))
{
	struct i2c_algo_bit_data *bit_adap = adap->algo_data;
	int ret;

	if (bit_test) {
		ret = test_bus(adap);
		if (bit_test >= 2 && ret < 0)
			return -ENODEV;
	}


	adap->algo = &i2c_bit_algo;
	adap->retries = 3;

	ret = add_adapter(adap);
	if (ret < 0)
		return ret;


	if (bit_adap->getscl == NULL) {
		dev_warn(&adap->dev, "Not I2C compliant: can't read SCL\n");
		dev_warn(&adap->dev, "Bus may be unreliable\n");
	}
	return 0;
}
