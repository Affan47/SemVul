bmg160_chip_init(struct bmg160_data *data)
{
	int ret;
	unsigned int val;


	regmap_write(data->regmap, BMG160_GYRO_REG_RESET,
		     BMG160_GYRO_RESET_VAL);
	usleep_range(30000, 30700);

	ret = regmap_read(data->regmap, BMG160_REG_CHIP_ID, &val);
	if (ret < 0) {
		dev_err(data->dev, "Error reading reg_chip_id\n");
		return ret;
	}

	dev_dbg(data->dev, "Chip Id %x\n", val);
	if (val != BMG160_CHIP_ID_VAL) {
		dev_err(data->dev, "invalid chip %x\n", val);
		return -ENODEV;
	}

	ret = bmg160_set_mode(data, BMG160_MODE_NORMAL);
	if (ret < 0)
		return ret;


	usleep_range(500, 1000);


	ret = bmg160_set_bw(data, BMG160_DEF_BW);
	if (ret < 0)
		return ret;


	ret = regmap_write(data->regmap, BMG160_REG_RANGE, BMG160_RANGE_500DPS);
	if (ret < 0) {
		dev_err(data->dev, "Error writing reg_range\n");
		return ret;
	}
	data->dps_range = BMG160_RANGE_500DPS;

	ret = regmap_read(data->regmap, BMG160_REG_SLOPE_THRES, &val);
	if (ret < 0) {
		dev_err(data->dev, "Error reading reg_slope_thres\n");
		return ret;
	}
	data->slope_thres = val;


	ret = regmap_update_bits(data->regmap, BMG160_REG_INT_EN_1,
				 BMG160_INT1_BIT_OD, 0);
	if (ret < 0) {
		dev_err(data->dev, "Error updating bits in reg_int_en_1\n");
		return ret;
	}

	ret = regmap_write(data->regmap, BMG160_REG_INT_RST_LATCH,
			   BMG160_INT_MODE_LATCH_INT |
			   BMG160_INT_MODE_LATCH_RESET);
	if (ret < 0) {
		dev_err(data->dev,
			"Error writing reg_motion_intr\n");
		return ret;
	}

	return 0;
}
