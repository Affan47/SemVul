cc10001_adc_channel_init(struct iio_dev *indio_dev,
				    unsigned long channel_map)
{
	struct iio_chan_spec *chan_array, *timestamp;
	unsigned int bit, idx = 0;

	indio_dev->num_channels = bitmap_weight(&channel_map,
						CC10001_ADC_NUM_CHANNELS) + 1;

	chan_array = devm_kcalloc(&indio_dev->dev, indio_dev->num_channels,
				  sizeof(struct iio_chan_spec),
				  GFP_KERNEL);
	if (!chan_array)
		return -ENOMEM;

	for_each_set_bit(bit, &channel_map, CC10001_ADC_NUM_CHANNELS) {
		struct iio_chan_spec *chan = &chan_array[idx];

		chan->type = IIO_VOLTAGE;
		chan->indexed = 1;
		chan->channel = bit;
		chan->scan_index = idx;
		chan->scan_type.sign = 'u';
		chan->scan_type.realbits = 10;
		chan->scan_type.storagebits = 16;
		chan->info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE);
		chan->info_mask_separate = BIT(IIO_CHAN_INFO_RAW);
		idx++;
	}

	timestamp = &chan_array[idx];
	timestamp->type = IIO_TIMESTAMP;
	timestamp->channel = -1;
	timestamp->scan_index = idx;
	timestamp->scan_type.sign = 's';
	timestamp->scan_type.realbits = 64;
	timestamp->scan_type.storagebits = 64;

	indio_dev->channels = chan_array;

	return 0;
}
