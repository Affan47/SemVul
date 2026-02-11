ltr501_read_ps(struct ltr501_data *data)
{
	int ret, status;

	ret = ltr501_drdy(data, LTR501_STATUS_PS_RDY);
	if (ret < 0)
		return ret;

	ret = regmap_bulk_read(data->regmap, LTR501_PS_DATA,
			       &status, 2);
	if (ret < 0)
		return ret;

	return status;
}
