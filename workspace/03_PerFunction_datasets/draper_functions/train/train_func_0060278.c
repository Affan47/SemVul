bmg160_set_bw(struct bmg160_data *data, int val)
{
	int ret;
	int bw_bits;

	bw_bits = bmg160_convert_freq_to_bit(val);
	if (bw_bits < 0)
		return bw_bits;

	ret = regmap_write(data->regmap, BMG160_REG_PMU_BW, bw_bits);
	if (ret < 0) {
		dev_err(data->dev, "Error writing reg_pmu_bw\n");
		return ret;
	}

	data->bw_bits = bw_bits;

	return 0;
}
