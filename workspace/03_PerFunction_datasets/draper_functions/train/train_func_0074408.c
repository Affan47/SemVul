i2c_is_busy_wait(struct saa7134_dev *dev)
{
	enum i2c_status status;
	int count;

	for (count = 0; count < I2C_WAIT_RETRY; count++) {
		status = i2c_get_status(dev);
		if (!i2c_is_busy(status))
			break;
		saa_wait(I2C_WAIT_DELAY);
	}
	if (I2C_WAIT_RETRY == count)
		return false;
	return true;
}
