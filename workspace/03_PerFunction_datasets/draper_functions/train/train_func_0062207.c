lm25066_read_word_data(struct i2c_client *client, int page, int reg)
{
	const struct pmbus_driver_info *info = pmbus_get_driver_info(client);
	const struct lm25066_data *data = to_lm25066_data(info);
	int ret;

	switch (reg) {
	case PMBUS_VIRT_READ_VMON:
		ret = pmbus_read_word_data(client, 0, LM25066_READ_VAUX);
		if (ret < 0)
			break;

		switch (data->id) {
		case lm25056:

			ret = DIV_ROUND_CLOSEST(ret * 293, 6140);
			break;
		case lm25063:

			ret = DIV_ROUND_CLOSEST(ret * 20, 625);
			break;
		case lm25066:

			ret = DIV_ROUND_CLOSEST(ret * 2832, 45400);
			break;
		case lm5064:

			ret = DIV_ROUND_CLOSEST(ret * 70, 453);
			break;
		case lm5066:

			ret = DIV_ROUND_CLOSEST(ret * 725, 2180);
			break;
		}
		break;
	case PMBUS_READ_IIN:
		ret = pmbus_read_word_data(client, 0, LM25066_MFR_READ_IIN);
		break;
	case PMBUS_READ_PIN:
		ret = pmbus_read_word_data(client, 0, LM25066_MFR_READ_PIN);
		break;
	case PMBUS_IIN_OC_WARN_LIMIT:
		ret = pmbus_read_word_data(client, 0,
					   LM25066_MFR_IIN_OC_WARN_LIMIT);
		break;
	case PMBUS_PIN_OP_WARN_LIMIT:
		ret = pmbus_read_word_data(client, 0,
					   LM25066_MFR_PIN_OP_WARN_LIMIT);
		break;
	case PMBUS_VIRT_READ_VIN_AVG:
		ret = pmbus_read_word_data(client, 0, LM25066_READ_AVG_VIN);
		break;
	case PMBUS_VIRT_READ_VOUT_AVG:
		ret = pmbus_read_word_data(client, 0, LM25066_READ_AVG_VOUT);
		break;
	case PMBUS_VIRT_READ_IIN_AVG:
		ret = pmbus_read_word_data(client, 0, LM25066_READ_AVG_IIN);
		break;
	case PMBUS_VIRT_READ_PIN_AVG:
		ret = pmbus_read_word_data(client, 0, LM25066_READ_AVG_PIN);
		break;
	case PMBUS_VIRT_READ_PIN_MAX:
		ret = pmbus_read_word_data(client, 0, LM25066_READ_PIN_PEAK);
		break;
	case PMBUS_VIRT_RESET_PIN_HISTORY:
		ret = 0;
		break;
	default:
		ret = -ENODATA;
		break;
	}
	return ret;
}
