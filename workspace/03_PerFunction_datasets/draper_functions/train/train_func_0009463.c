upd64083_read(struct v4l2_subdev *sd, u8 reg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	u8 buf[7];

	if (reg >= sizeof(buf))
		return 0xff;
	i2c_master_recv(client, buf, sizeof(buf));
	return buf[reg];
}
