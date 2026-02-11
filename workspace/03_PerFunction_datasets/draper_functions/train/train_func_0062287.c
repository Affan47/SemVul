nau7802_read_conversion(struct nau7802_state *st)
{
	int data;

	mutex_lock(&st->data_lock);
	data = i2c_smbus_read_byte_data(st->client, NAU7802_REG_ADC_B2);
	if (data < 0)
		goto nau7802_read_conversion_out;
	st->last_value = data << 16;

	data = i2c_smbus_read_byte_data(st->client, NAU7802_REG_ADC_B1);
	if (data < 0)
		goto nau7802_read_conversion_out;
	st->last_value |= data << 8;

	data = i2c_smbus_read_byte_data(st->client, NAU7802_REG_ADC_B0);
	if (data < 0)
		goto nau7802_read_conversion_out;
	st->last_value |= data;

	st->last_value = sign_extend32(st->last_value, 23);

nau7802_read_conversion_out:
	mutex_unlock(&st->data_lock);

	return data;
}
