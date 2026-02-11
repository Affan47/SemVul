ad5398_set_current_limit(struct regulator_dev *rdev, int min_uA, int max_uA)
{
	struct ad5398_chip_info *chip = rdev_get_drvdata(rdev);
	struct i2c_client *client = chip->client;
	unsigned range_uA = chip->max_uA - chip->min_uA;
	unsigned selector;
	unsigned short data;
	int ret;

	if (min_uA < chip->min_uA)
		min_uA = chip->min_uA;
	if (max_uA > chip->max_uA)
		max_uA = chip->max_uA;

	if (min_uA > chip->max_uA || max_uA < chip->min_uA)
		return -EINVAL;

	selector = DIV_ROUND_UP((min_uA - chip->min_uA) * chip->current_level,
				range_uA);
	if (ad5398_calc_current(chip, selector) > max_uA)
		return -EINVAL;

	dev_dbg(&client->dev, "changing current %duA\n",
		ad5398_calc_current(chip, selector));


	ret = ad5398_read_reg(client, &data);
	if (ret < 0)
		return ret;


	selector = (selector << chip->current_offset) & chip->current_mask;
	data = (unsigned short)selector | (data & AD5398_CURRENT_EN_MASK);


	ret = ad5398_write_reg(client, data);

	return ret;
}
