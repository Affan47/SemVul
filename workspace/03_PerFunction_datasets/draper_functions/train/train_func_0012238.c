mlx90614_probe_num_ir_sensors(struct i2c_client *client)
{
	s32 ret;

	ret = i2c_smbus_read_word_data(client, MLX90614_CONFIG);

	if (ret < 0)
		return ret;

	return (ret & MLX90614_CONFIG_DUAL_MASK) ? 1 : 0;
}
