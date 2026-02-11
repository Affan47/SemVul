adt7470_init_client(struct i2c_client *client)
{
	int reg = i2c_smbus_read_byte_data(client, ADT7470_REG_CFG);

	if (reg < 0) {
		dev_err(&client->dev, "cannot read configuration register\n");
	} else {

		i2c_smbus_write_byte_data(client, ADT7470_REG_CFG, reg | 3);
	}
}
