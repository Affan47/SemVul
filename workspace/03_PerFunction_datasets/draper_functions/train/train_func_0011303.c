hid_sensor_push_data(struct iio_dev *indio_dev, u8 *data, int len)
{
	dev_dbg(&indio_dev->dev, "hid_sensor_push_data >>\n");
	iio_push_to_buffers(indio_dev, (u8 *)data);
	dev_dbg(&indio_dev->dev, "hid_sensor_push_data <<\n");

}
