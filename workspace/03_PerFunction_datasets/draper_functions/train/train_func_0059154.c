apds9300_set_thresh_hi(struct apds9300_data *data, int value)
{
	int ret;

	if (!data->power_state)
		return -EBUSY;

	if (value > APDS9300_THRESH_MAX)
		return -EINVAL;

	ret = i2c_smbus_write_word_data(data->client, APDS9300_THRESHHIGHLOW
			| APDS9300_CMD | APDS9300_WORD, value);
	if (ret) {
		dev_err(&data->client->dev, "failed to set thresh_hi\n");
		return ret;
	}
	data->thresh_hi = value;

	return 0;
}
