i2c_get_funcs(int i2cbus)
{
	unsigned long funcs;
	int file;
	char filename[20];
	enum adt ret;

	file = open_i2c_dev(i2cbus, filename, sizeof(filename), 1);
	if (file < 0)
		return adt_unknown;

	if (ioctl(file, I2C_FUNCS, &funcs) < 0)
		ret = adt_unknown;
	else if (funcs & I2C_FUNC_I2C)
		ret = adt_i2c;
	else if (funcs & (I2C_FUNC_SMBUS_BYTE |
			  I2C_FUNC_SMBUS_BYTE_DATA |
			  I2C_FUNC_SMBUS_WORD_DATA))
		ret = adt_smbus;
	else
		ret = adt_dummy;

	close(file);
	return ret;
}
