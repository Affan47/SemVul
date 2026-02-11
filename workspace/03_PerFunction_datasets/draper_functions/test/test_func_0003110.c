acpi_als_read_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan, int *val,
			     int *val2, long mask)
{
	struct acpi_als *als = iio_priv(indio_dev);
	s32 temp_val;
	int ret;

	if ((mask != IIO_CHAN_INFO_PROCESSED) && (mask != IIO_CHAN_INFO_RAW))
		return -EINVAL;


	if (chan->type != IIO_LIGHT)
		return -EINVAL;

	ret = acpi_als_read_value(als, ACPI_ALS_ILLUMINANCE, &temp_val);
	if (ret < 0)
		return ret;

	*val = temp_val;

	return IIO_VAL_INT;
}
