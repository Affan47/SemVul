i2c_algo_dp_aux_get_byte(struct i2c_adapter *adapter, u8 *byte_ret)
{
	struct i2c_algo_dp_aux_data *algo_data = adapter->algo_data;
	int ret;

	if (!algo_data->running)
		return -EIO;

	ret = i2c_algo_dp_aux_transaction(adapter, MODE_I2C_READ, 0, byte_ret);
	return ret;
}
