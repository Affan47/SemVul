stk3310_irq_event_handler(int irq, void *private)
{
	int ret;
	unsigned int dir;
	u64 event;

	struct iio_dev *indio_dev = private;
	struct stk3310_data *data = iio_priv(indio_dev);


	mutex_lock(&data->lock);
	ret = regmap_field_read(data->reg_flag_nf, &dir);
	if (ret < 0) {
		dev_err(&data->client->dev, "register read failed\n");
		mutex_unlock(&data->lock);
		return ret;
	}
	event = IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, 1,
				     IIO_EV_TYPE_THRESH,
				     (dir ? IIO_EV_DIR_FALLING :
					    IIO_EV_DIR_RISING));
	iio_push_event(indio_dev, event, data->timestamp);


	ret = regmap_field_write(data->reg_flag_psint, 0);
	if (ret < 0)
		dev_err(&data->client->dev, "failed to reset interrupts\n");
	mutex_unlock(&data->lock);

	return IRQ_HANDLED;
}
