sht15_send_status(struct sht15_data *data, u8 status)
{
	int err;

	err = sht15_send_cmd(data, SHT15_WRITE_STATUS);
	if (err)
		return err;
	err = gpio_direction_output(data->pdata->gpio_data, 1);
	if (err)
		return err;
	ndelay(SHT15_TSU);
	sht15_send_byte(data, status);
	err = sht15_wait_for_response(data);
	if (err)
		return err;

	data->val_status = status;
	return 0;
}
