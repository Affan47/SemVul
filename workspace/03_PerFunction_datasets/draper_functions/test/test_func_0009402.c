bmc150_magn_get_odr(struct bmc150_magn_data *data, int *val)
{
	int ret, reg_val;
	u8 i, odr_val;

	ret = regmap_read(data->regmap, BMC150_MAGN_REG_OPMODE_ODR, &reg_val);
	if (ret < 0)
		return ret;
	odr_val = (reg_val & BMC150_MAGN_MASK_ODR) >> BMC150_MAGN_SHIFT_ODR;

	for (i = 0; i < ARRAY_SIZE(bmc150_magn_samp_freq_table); i++)
		if (bmc150_magn_samp_freq_table[i].reg_val == odr_val) {
			*val = bmc150_magn_samp_freq_table[i].freq;
			return 0;
		}

	return -EINVAL;
}
