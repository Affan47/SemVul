power_smbus_write_byte_data(
	struct cpssp *cpssp,
	unsigned char addr,
	unsigned char cmd,
	unsigned char data
)
{
	int ret;
	unsigned char buf[2];
	buf[0] = cmd;
	buf[1] = data;

	ret = sig_i2c_bus_write_bytes(
		cpssp->sig_i2cbus, cpssp, addr & (~1), 2, buf);
	sig_i2c_bus_stop_transaction(cpssp->sig_i2cbus, cpssp);

	if (ret == 2) {
		return 0;
	}

	return -1;
}
