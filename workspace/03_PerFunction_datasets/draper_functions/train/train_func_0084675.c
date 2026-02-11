cx231xx_i2c_check_for_device(struct i2c_adapter *i2c_adap,
					const struct i2c_msg *msg)
{
	struct cx231xx_i2c *bus = i2c_adap->algo_data;
	struct cx231xx *dev = bus->dev;
	struct cx231xx_i2c_xfer_data req_data;
	int status = 0;
	u8 buf[1];


	req_data.dev_addr = msg->addr;
	req_data.direction = I2C_M_RD;
	req_data.saddr_len = 0;
	req_data.saddr_dat = 0;
	req_data.buf_size = 1;
	req_data.p_buffer = buf;


	status = dev->cx231xx_send_usb_command(bus, &req_data);

	return status < 0 ? status : 0;
}
