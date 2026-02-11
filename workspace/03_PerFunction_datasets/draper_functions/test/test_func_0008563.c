ov2659_write(struct i2c_client *client, u16 reg, u8 val)
{
	struct i2c_msg msg;
	u8 buf[3];
	int ret;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xFF;
	buf[2] = val;

	msg.addr = client->addr;
	msg.flags = client->flags;
	msg.buf = buf;
	msg.len = sizeof(buf);

	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret >= 0)
		return 0;

	dev_dbg(&client->dev,
		"ov2659 write reg(0x%x val:0x%x) failed !\n", reg, val);

	return ret;
}
