tmp006_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val,
			    int val2,
			    long mask)
{
	struct tmp006_data *data = iio_priv(indio_dev);
	int i;

	if (mask != IIO_CHAN_INFO_SAMP_FREQ)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(tmp006_freqs); i++)
		if ((val == tmp006_freqs[i][0]) &&
		    (val2 == tmp006_freqs[i][1])) {
			data->config &= ~TMP006_CONFIG_CR_MASK;
			data->config |= i << TMP006_CONFIG_CR_SHIFT;

			return i2c_smbus_write_word_swapped(data->client,
							    TMP006_CONFIG,
							    data->config);

		}
	return -EINVAL;
}
