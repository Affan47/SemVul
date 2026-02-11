taos_instantiate_device(struct i2c_adapter *adapter)
{
	if (!strncmp(adapter->name, "TAOS TSL2550 EVM", 16)) {
		dev_info(&adapter->dev, "Instantiating device %s at 0x%02x\n",
			tsl2550_info.type, tsl2550_info.addr);
		return i2c_new_device(adapter, &tsl2550_info);
	}

	return NULL;
}
