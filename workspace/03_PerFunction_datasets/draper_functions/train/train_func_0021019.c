cm3323_set_it_bits(struct cm3323_data *data, int val, int val2)
{
	int i, ret;
	u16 reg_conf;

	for (i = 0; i < ARRAY_SIZE(cm3323_int_time); i++) {
		if (val == cm3323_int_time[i].val &&
		    val2 == cm3323_int_time[i].val2) {
			reg_conf = data->reg_conf & ~CM3323_CONF_IT_MASK;
			reg_conf |= i << CM3323_CONF_IT_SHIFT;

			ret = i2c_smbus_write_word_data(data->client,
							CM3323_CMD_CONF,
							reg_conf);
			if (ret < 0)
				return ret;

			data->reg_conf = reg_conf;

			return 0;
		}
	}

	return -EINVAL;
}
