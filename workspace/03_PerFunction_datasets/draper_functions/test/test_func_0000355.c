s5m8767_rtc_init_reg(struct s5m_rtc_info *info)
{
	u8 data[2];
	int ret;

	switch (info->device_type) {
	case S5M8763X:
	case S5M8767X:

		ret = regmap_update_bits(info->regmap, S5M_RTC_UDR_CON,
				S5M_RTC_UDR_T_MASK, S5M_RTC_UDR_T_450_US);
		if (ret < 0)
			dev_err(info->dev, "%s: fail to change UDR time: %d\n",
					__func__, ret);


		data[0] = (1 << BCD_EN_SHIFT) | (1 << MODEL24_SHIFT);
		data[1] = (0 << BCD_EN_SHIFT) | (1 << MODEL24_SHIFT);

		ret = regmap_raw_write(info->regmap, S5M_ALARM0_CONF, data, 2);
		break;

	case S2MPS14X:
	case S2MPS13X:
		data[0] = (0 << BCD_EN_SHIFT) | (1 << MODEL24_SHIFT);
		ret = regmap_write(info->regmap, info->regs->ctrl, data[0]);
		if (ret < 0)
			break;


		ret = s5m8767_rtc_set_alarm_reg(info);
		break;

	default:
		return -EINVAL;
	}

	info->rtc_24hr_mode = 1;
	if (ret < 0) {
		dev_err(info->dev, "%s: fail to write controlm reg(%d)\n",
			__func__, ret);
		return ret;
	}

	return ret;
}
