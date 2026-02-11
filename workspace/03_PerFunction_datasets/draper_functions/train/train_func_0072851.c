s5k4ecgx_i2c_write(struct i2c_client *client, u16 addr, u16 val)
{
	u8 buf[4] = { addr >> 8, addr & 0xff, val >> 8, val & 0xff };

	int ret = i2c_master_send(client, buf, 4);
	v4l2_dbg(4, debug, client, "i2c_write: 0x%04x : 0x%04x\n", addr, val);

	return ret == 4 ? 0 : ret;
}
