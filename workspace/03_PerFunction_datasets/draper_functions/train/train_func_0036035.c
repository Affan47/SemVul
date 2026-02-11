as3935_suspend(struct device *dev)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct as3935_state *st = iio_priv(indio_dev);
	int val, ret;

	mutex_lock(&st->lock);
	ret = as3935_read(st, AS3935_AFE_GAIN, &val);
	if (ret)
		goto err_suspend;
	val |= AS3935_AFE_PWR_BIT;

	ret = as3935_write(st, AS3935_AFE_GAIN, val);

err_suspend:
	mutex_unlock(&st->lock);

	return ret;
}
