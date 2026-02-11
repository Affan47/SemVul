st_sensors_read_axis_data(struct iio_dev *indio_dev,
				struct iio_chan_spec const *ch, int *data)
{
	int err;
	u8 *outdata;
	struct st_sensor_data *sdata = iio_priv(indio_dev);
	unsigned int byte_for_channel = ch->scan_type.realbits >> 3;

	byte_for_channel = DIV_ROUND_UP(ch->scan_type.realbits +
					ch->scan_type.shift, 8);
	outdata = kmalloc(byte_for_channel, GFP_KERNEL);
	if (!outdata)
		return -ENOMEM;

	err = sdata->tf->read_multiple_byte(&sdata->tb, sdata->dev,
				ch->address, byte_for_channel,
				outdata, sdata->multiread_bit);
	if (err < 0)
		goto st_sensors_free_memory;

	if (byte_for_channel == 1)
		*data = (s8)*outdata;
	else if (byte_for_channel == 2)
		*data = (s16)get_unaligned_le16(outdata);
	else if (byte_for_channel == 3)
		*data = (s32)st_sensors_get_unaligned_le24(outdata);

st_sensors_free_memory:
	kfree(outdata);

	return err;
}
