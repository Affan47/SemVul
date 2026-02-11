ad7879_i2c_multi_read(struct device *dev,
				 u8 first_reg, u8 count, u16 *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	u8 idx;

	i2c_smbus_read_i2c_block_data(client, first_reg, count * 2, (u8 *)buf);

	for (idx = 0; idx < count; ++idx)
		buf[idx] = swab16(buf[idx]);

	return 0;
}
