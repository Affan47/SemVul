emc6w201_write8(struct i2c_client *client, u8 reg, u8 val)
{
	int err;

	err = i2c_smbus_write_byte_data(client, reg, val);
	if (unlikely(err < 0))
		dev_err(&client->dev, "%d-bit %s failed at 0x%02x\n",
			8, "write", reg);

	return err;
}
