bh1770_lux_rate(struct bh1770_chip *chip, int rate_index)
{

	if (pm_runtime_suspended(&chip->client->dev))
		return 0;


	if (chip->prox_enable_count)
		rate_index = 0;

	return i2c_smbus_write_byte_data(chip->client,
					BH1770_ALS_MEAS_RATE,
					rate_index);
}
