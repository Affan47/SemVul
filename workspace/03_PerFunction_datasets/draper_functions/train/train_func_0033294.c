ov772x_mask_set(struct i2c_client *client, u8  command, u8  mask,
			   u8  set)
{
	s32 val = ov772x_read(client, command);
	if (val < 0)
		return val;

	val &= ~mask;
	val |= set & mask;

	return ov772x_write(client, command, val);
}
