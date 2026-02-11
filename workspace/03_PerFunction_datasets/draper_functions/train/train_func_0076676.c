ds620_init_client(struct i2c_client *client)
{
	struct ds620_platform_data *ds620_info = dev_get_platdata(&client->dev);
	u16 conf, new_conf;

	new_conf = conf =
	    i2c_smbus_read_word_swapped(client, DS620_REG_CONF);


	new_conf &= ~DS620_REG_CONFIG_1SHOT;

	new_conf |= DS620_REG_CONFIG_PO2;

	if (ds620_info && ds620_info->pomode == 1)
		new_conf &= ~DS620_REG_CONFIG_PO1;
	else if (ds620_info && ds620_info->pomode == 2)
		new_conf |= DS620_REG_CONFIG_PO1;
	else
		new_conf &= ~DS620_REG_CONFIG_PO2;

	new_conf |= DS620_REG_CONFIG_R1 | DS620_REG_CONFIG_R0;

	if (conf != new_conf)
		i2c_smbus_write_word_swapped(client, DS620_REG_CONF, new_conf);


	i2c_smbus_write_byte(client, DS620_COM_START);
}
