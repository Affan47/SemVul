menf21bmc_wdt_set_bootstatus(struct menf21bmc_wdt *data)
{
	int rst_rsn;

	rst_rsn = i2c_smbus_read_byte_data(data->i2c_client, BMC_CMD_RST_RSN);
	if (rst_rsn < 0)
		return rst_rsn;

	if (rst_rsn == 0x02)
		data->wdt.bootstatus |= WDIOF_CARDRESET;
	else if (rst_rsn == 0x05)
		data->wdt.bootstatus |= WDIOF_EXTERN1;
	else if (rst_rsn == 0x06)
		data->wdt.bootstatus |= WDIOF_EXTERN2;
	else if (rst_rsn == 0x0A)
		data->wdt.bootstatus |= WDIOF_POWERUNDER;

	return 0;
}
