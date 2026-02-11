jsa1212_pxs_enable(struct jsa1212_data *data, u8 status)
{
	int ret;

	ret = regmap_update_bits(data->regmap, JSA1212_CONF_REG,
				JSA1212_CONF_PXS_MASK,
				status);
	if (ret < 0)
		return ret;

	data->pxs_en = !!status;

	return 0;
}
