adis_reset(struct adis *adis)
{
	int ret;

	ret = adis_write_reg_8(adis, adis->data->glob_cmd_reg,
			ADIS_GLOB_CMD_SW_RESET);
	if (ret)
		dev_err(&adis->spi->dev, "Failed to reset device: %d\n", ret);

	return ret;
}
