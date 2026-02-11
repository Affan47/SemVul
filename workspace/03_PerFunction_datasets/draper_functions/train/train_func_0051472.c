rt5033_battery_get_watt_prop(struct i2c_client *client,
		enum power_supply_property psp)
{
	struct rt5033_battery *battery = i2c_get_clientdata(client);
	unsigned int regh, regl;
	int ret;
	u32 msb, lsb;

	switch (psp) {
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		regh = RT5033_FUEL_REG_VBAT_H;
		regl = RT5033_FUEL_REG_VBAT_L;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_AVG:
		regh = RT5033_FUEL_REG_AVG_VOLT_H;
		regl = RT5033_FUEL_REG_AVG_VOLT_L;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_OCV:
		regh = RT5033_FUEL_REG_OCV_H;
		regl = RT5033_FUEL_REG_OCV_L;
		break;
	default:
		return -EINVAL;
	}

	regmap_read(battery->regmap, regh, &msb);
	regmap_read(battery->regmap, regl, &lsb);

	ret = ((msb << 4) + (lsb >> 4)) * 1250 / 1000;

	return ret;
}
