menf21bmc_wdt_exit_prod_mode(struct i2c_client *client)
{
	int val, ret;

	val = i2c_smbus_read_byte_data(client, BMC_CMD_WDT_PROD_STAT);
	if (val < 0)
		return val;


	if (val == 0x00) {
		dev_info(&client->dev,
			"BMC in production mode. Exit production mode\n");

		ret = i2c_smbus_write_byte(client, BMC_CMD_WDT_EXIT_PROD);
		if (ret < 0)
			return ret;
	}

	return 0;
}
