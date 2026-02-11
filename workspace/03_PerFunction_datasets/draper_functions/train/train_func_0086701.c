w83781d_read_value_i2c(struct w83781d_data *data, u16 reg)
{
	struct i2c_client *client = data->client;
	int res, bank;
	struct i2c_client *cl;

	bank = (reg >> 8) & 0x0f;
	if (bank > 2)

		i2c_smbus_write_byte_data(client, W83781D_REG_BANK,
					  bank);
	if (bank == 0 || bank > 2) {
		res = i2c_smbus_read_byte_data(client, reg & 0xff);
	} else {

		cl = data->lm75[bank - 1];

		switch (reg & 0xff) {
		case 0x50:
			res = i2c_smbus_read_word_swapped(cl, 0);
			break;
		case 0x52:
			res = i2c_smbus_read_byte_data(cl, 1);
			break;
		case 0x53:
			res = i2c_smbus_read_word_swapped(cl, 2);
			break;
		case 0x55:
		default:
			res = i2c_smbus_read_word_swapped(cl, 3);
			break;
		}
	}
	if (bank > 2)
		i2c_smbus_write_byte_data(client, W83781D_REG_BANK, 0);

	return res;
}
