skystar2_rev26_attach(struct flexcop_device *fc,
	struct i2c_adapter *i2c)
{
	fc->fe = dvb_attach(stv0299_attach, &samsung_tbmu24112_config, i2c);
	if (!fc->fe)
		return 0;

	if (!dvb_attach(dvb_pll_attach, fc->fe, 0x61, i2c,
			DVB_PLL_SAMSUNG_TBMU24112))
		return 0;

	fc->fe->ops.set_voltage = flexcop_set_voltage;
	fc->fe_sleep = fc->fe->ops.sleep;
	fc->fe->ops.sleep = flexcop_sleep;
	return 1;

}
