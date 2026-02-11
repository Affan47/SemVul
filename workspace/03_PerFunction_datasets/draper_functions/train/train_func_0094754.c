kxtj9_update_odr(struct kxtj9_data *tj9, unsigned int poll_interval)
{
	int err;
	int i;


	for (i = 0; i < ARRAY_SIZE(kxtj9_odr_table); i++) {
		tj9->data_ctrl = kxtj9_odr_table[i].mask;
		if (poll_interval < kxtj9_odr_table[i].cutoff)
			break;
	}

	err = i2c_smbus_write_byte_data(tj9->client, CTRL_REG1, 0);
	if (err < 0)
		return err;

	err = i2c_smbus_write_byte_data(tj9->client, DATA_CTRL, tj9->data_ctrl);
	if (err < 0)
		return err;

	err = i2c_smbus_write_byte_data(tj9->client, CTRL_REG1, tj9->ctrl_reg1);
	if (err < 0)
		return err;

	return 0;
}
