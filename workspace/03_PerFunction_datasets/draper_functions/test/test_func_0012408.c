dib8096p_tuner_rw_serpar(struct i2c_adapter *i2c_adap,
		struct i2c_msg msg[], int num)
{
	if (map_addr_to_serpar_number(&msg[0]) == 0) {
		if (num == 1)
			return dib8096p_tuner_write_serpar(i2c_adap, msg, 1);
		else
			return dib8096p_tuner_read_serpar(i2c_adap, msg, 2);
	}
	return num;
}
