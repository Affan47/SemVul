synaptics_i2c_reg_get(struct i2c_client *client, u16 reg)
{
	int ret;

	ret = i2c_smbus_write_byte_data(client, PAGE_SEL_REG, reg >> 8);
	if (ret == 0)
		ret = i2c_smbus_read_byte_data(client, reg & 0xff);

	return ret;
}
