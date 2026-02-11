ltc3883_read_word_data(struct i2c_client *client, int page, int reg)
{
	const struct pmbus_driver_info *info = pmbus_get_driver_info(client);
	struct ltc2978_data *data = to_ltc2978_data(info);
	int ret;

	switch (reg) {
	case PMBUS_VIRT_READ_IIN_MAX:
		ret = ltc_get_max(data, client, page, LTC3883_MFR_IIN_PEAK,
				  &data->iin_max);
		break;
	case PMBUS_VIRT_RESET_IIN_HISTORY:
		ret = 0;
		break;
	default:
		ret = ltc3880_read_word_data(client, page, reg);
		break;
	}
	return ret;
}
