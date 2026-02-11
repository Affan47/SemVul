ds1307_native_smbus_read_block_data(const struct i2c_client *client,
				u8 command, u8 length, u8 *values)
{
	u8 suboffset = 0;

	if (length <= I2C_SMBUS_BLOCK_MAX)
		return i2c_smbus_read_i2c_block_data(client,
					command, length, values);

	while (suboffset < length) {
		s32 retval = i2c_smbus_read_i2c_block_data(client,
				command + suboffset,
				min(I2C_SMBUS_BLOCK_MAX, length - suboffset),
				values + suboffset);
		if (retval < 0)
			return retval;

		suboffset += I2C_SMBUS_BLOCK_MAX;
	}
	return length;
}
