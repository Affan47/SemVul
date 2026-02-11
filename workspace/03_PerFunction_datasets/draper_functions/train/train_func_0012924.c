acknak(struct i2c_adapter *i2c_adap, int is_ack)
{
	struct i2c_algo_bit_data *adap = i2c_adap->algo_data;


	if (is_ack)
		setsda(adap, 0);
	udelay((adap->udelay + 1) / 2);
	if (sclhi(adap) < 0) {
		dev_err(&i2c_adap->dev, "readbytes: ack/nak timeout\n");
		return -ETIMEDOUT;
	}
	scllo(adap);
	return 0;
}
