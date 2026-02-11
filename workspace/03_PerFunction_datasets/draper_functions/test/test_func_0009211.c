power_smbus_read_byte_data(
	struct cpssp *cpssp,
	unsigned char addr,
	unsigned char cmd,
	unsigned char *data
)
{
	int ret;

	ret = sig_i2c_bus_write_bytes(
		cpssp->sig_i2cbus, cpssp, addr & (~1), 1, &cmd);
	if (ret != 1) {
		return -1;
	}

	sig_i2c_bus_read_bytes(cpssp->sig_i2cbus, cpssp, addr | 1, 1, data);
	sig_i2c_bus_stop_transaction(cpssp->sig_i2cbus, cpssp);
	return 0;
}
