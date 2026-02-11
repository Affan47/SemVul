elan_smbus_get_num_traces(struct i2c_client *client,
				     unsigned int *x_traces,
				     unsigned int *y_traces)
{
	int error;
	u8 val[3];

	error = i2c_smbus_read_block_data(client,
					  ETP_SMBUS_XY_TRACENUM_CMD, val);
	if (error) {
		dev_err(&client->dev, "failed to get trace info: %d\n", error);
		return error;
	}

	*x_traces = val[1];
	*y_traces = val[2];

	return 0;
}
