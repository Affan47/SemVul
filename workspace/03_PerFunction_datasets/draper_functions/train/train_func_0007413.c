ltc294x_reset(const struct ltc294x_info *info, int prescaler_exp)
{
	int ret;
	u8 value;
	u8 control;


	ret = ltc294x_read_regs(info->client, LTC294X_REG_CONTROL, &value, 1);
	if (ret < 0) {
		dev_err(&info->client->dev,
			"Could not read registers from device\n");
		goto error_exit;
	}

	control = LTC294X_REG_CONTROL_PRESCALER_SET(prescaler_exp) |
				LTC294X_REG_CONTROL_ALCC_CONFIG_DISABLED;

	if (info->num_regs == LTC2943_NUM_REGS)
		control |= LTC2943_REG_CONTROL_MODE_SCAN;

	if (value != control) {
		ret = ltc294x_write_regs(info->client,
			LTC294X_REG_CONTROL, &control, 1);
		if (ret < 0) {
			dev_err(&info->client->dev,
				"Could not write register\n");
			goto error_exit;
		}
	}

	return 0;

error_exit:
	return ret;
}
