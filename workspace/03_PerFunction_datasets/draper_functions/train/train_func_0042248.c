adp8860_clr_bits(struct i2c_client *client, int reg, uint8_t bit_mask)
{
	struct adp8860_bl *data = i2c_get_clientdata(client);
	uint8_t reg_val;
	int ret;

	mutex_lock(&data->lock);

	ret = adp8860_read(client, reg, &reg_val);

	if (!ret && (reg_val & bit_mask)) {
		reg_val &= ~bit_mask;
		ret = adp8860_write(client, reg, reg_val);
	}

	mutex_unlock(&data->lock);
	return ret;
}
