tps51632_init_dcdc(struct tps51632_chip *tps,
		struct tps51632_regulator_platform_data *pdata)
{
	int ret;
	uint8_t	control = 0;
	int vsel;

	if (!pdata->enable_pwm_dvfs)
		goto skip_pwm_config;

	control |= TPS51632_DVFS_PWMEN;
	vsel = TPS51632_VOLT_VSEL(pdata->base_voltage_uV);
	ret = regmap_write(tps->regmap, TPS51632_VOLTAGE_BASE_REG, vsel);
	if (ret < 0) {
		dev_err(tps->dev, "BASE reg write failed, err %d\n", ret);
		return ret;
	}

	if (pdata->dvfs_step_20mV)
		control |= TPS51632_DVFS_STEP_20;

	if (pdata->max_voltage_uV) {
		unsigned int vmax;


		ret = regmap_read(tps->regmap, TPS51632_VMAX_REG, &vmax);
		if (ret < 0) {
			dev_err(tps->dev, "VMAX read failed, err %d\n", ret);
			return ret;
		}
		if (!(vmax & TPS51632_VMAX_LOCK)) {
			vsel = TPS51632_VOLT_VSEL(pdata->max_voltage_uV);
			ret = regmap_write(tps->regmap, TPS51632_VMAX_REG,
					vsel);
			if (ret < 0) {
				dev_err(tps->dev,
					"VMAX write failed, err %d\n", ret);
				return ret;
			}
		}
	}

skip_pwm_config:
	ret = regmap_write(tps->regmap, TPS51632_DVFS_CONTROL_REG, control);
	if (ret < 0)
		dev_err(tps->dev, "DVFS reg write failed, err %d\n", ret);
	return ret;
}
