osc_deviation(void *priv, s16 deviation, int flag)
{
	struct ngene_channel *chan = priv;
	struct i2c_adapter *adap = &chan->i2c_adapter;
	u16 data = 0;

	if (flag) {
		data = (u16) deviation;
		pr_info(DEVICE_NAME ": write deviation %d\n",
		       deviation);
		eeprom_write_ushort(adap, 0x1000 + chan->number, data);
	} else {
		if (eeprom_read_ushort(adap, 0x1000 + chan->number, &data))
			data = 0;
		pr_info(DEVICE_NAME ": read deviation %d\n",
		       (s16) data);
	}

	return (s16) data;
}
