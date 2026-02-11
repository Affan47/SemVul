cbus_i2c_smbus_xfer(struct i2c_adapter	*adapter,
			       u16			addr,
			       unsigned short		flags,
			       char			read_write,
			       u8			command,
			       int			size,
			       union i2c_smbus_data	*data)
{
	struct cbus_host *chost = i2c_get_adapdata(adapter);
	int ret;

	if (size != I2C_SMBUS_WORD_DATA)
		return -EINVAL;

	ret = cbus_transfer(chost, read_write == I2C_SMBUS_READ, addr,
			    command, data->word);
	if (ret < 0)
		return ret;

	if (read_write == I2C_SMBUS_READ)
		data->word = ret;

	return 0;
}
