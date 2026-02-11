pixcir_parse_dt(struct device *dev,
			   struct pixcir_i2c_ts_data *tsdata)
{
	const struct of_device_id *match;

	match = of_match_device(of_match_ptr(pixcir_of_match), dev);
	if (!match)
		return -EINVAL;

	tsdata->chip = (const struct pixcir_i2c_chip_data *)match->data;
	if (!tsdata->chip)
		return -EINVAL;

	return 0;
}
