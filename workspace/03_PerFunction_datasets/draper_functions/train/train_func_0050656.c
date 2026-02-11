stk3310_read_event(struct iio_dev *indio_dev,
			      const struct iio_chan_spec *chan,
			      enum iio_event_type type,
			      enum iio_event_direction dir,
			      enum iio_event_info info,
			      int *val, int *val2)
{
	u8 reg;
	__be16 buf;
	int ret;
	struct stk3310_data *data = iio_priv(indio_dev);

	if (info != IIO_EV_INFO_VALUE)
		return -EINVAL;


	if (dir == IIO_EV_DIR_RISING)
		reg = STK3310_REG_THDH_PS;
	else if (dir == IIO_EV_DIR_FALLING)
		reg = STK3310_REG_THDL_PS;
	else
		return -EINVAL;

	mutex_lock(&data->lock);
	ret = regmap_bulk_read(data->regmap, reg, &buf, 2);
	mutex_unlock(&data->lock);
	if (ret < 0) {
		dev_err(&data->client->dev, "register read failed\n");
		return ret;
	}
	*val = be16_to_cpu(buf);

	return IIO_VAL_INT;
}
