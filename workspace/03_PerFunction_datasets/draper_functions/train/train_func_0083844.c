em_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs,
	int num)
{
	struct em_i2c_device *priv = i2c_get_adapdata(adap);
	int ret, i;

	if (readb(priv->base + I2C_OFS_IICF0) & I2C_BIT_IICBSY)
		return -EAGAIN;

	for (i = 0; i < num; i++) {
		ret = __em_i2c_xfer(adap, &msgs[i], (i == (num - 1)));
		if (ret < 0)
			return ret;
	}


	return num;
}
