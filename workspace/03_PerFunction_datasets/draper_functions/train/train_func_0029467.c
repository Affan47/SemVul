rs5c372_get_trim(struct i2c_client *client, int *osc, int *trim)
{
	struct rs5c372 *rs5c372 = i2c_get_clientdata(client);
	u8 tmp = rs5c372->regs[RS5C372_REG_TRIM];

	if (osc)
		*osc = (tmp & RS5C372_TRIM_XSL) ? 32000 : 32768;

	if (trim) {
		dev_dbg(&client->dev, "%s: raw trim=%x\n", __func__, tmp);
		tmp &= RS5C372_TRIM_MASK;
		if (tmp & 0x3e) {
			int t = tmp & 0x3f;

			if (tmp & 0x40)
				t = (~t | (s8)0xc0) + 1;
			else
				t = t - 1;

			tmp = t * 2;
		} else
			tmp = 0;
		*trim = tmp;
	}

	return 0;
}
