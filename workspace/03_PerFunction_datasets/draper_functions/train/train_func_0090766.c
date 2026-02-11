ivch_write(struct intel_dvo_device *dvo, int addr, uint16_t data)
{
	struct ivch_priv *priv = dvo->dev_priv;
	struct i2c_adapter *adapter = dvo->i2c_bus;
	u8 out_buf[3];
	struct i2c_msg msg = {
		.addr = dvo->slave_addr,
		.flags = 0,
		.len = 3,
		.buf = out_buf,
	};

	out_buf[0] = addr;
	out_buf[1] = data & 0xff;
	out_buf[2] = data >> 8;

	if (i2c_transfer(adapter, &msg, 1) == 1)
		return true;

	if (!priv->quiet) {
		DRM_DEBUG_KMS("Unable to write register 0x%02x to %s:%d.\n",
			  addr, adapter->name, dvo->slave_addr);
	}

	return false;
}
