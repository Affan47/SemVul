s5k6aa_new_config_sync(struct i2c_client *client, int timeout,
				  int cid)
{
	unsigned long end = jiffies + msecs_to_jiffies(timeout);
	u16 reg = 1;
	int ret;

	ret = s5k6aa_write(client, REG_G_ACTIVE_PREV_CFG, cid);
	if (!ret)
		ret = s5k6aa_write(client, REG_G_PREV_CFG_CHG, 1);
	if (!ret)
		ret = s5k6aa_write(client, REG_G_NEW_CFG_SYNC, 1);
	if (timeout == 0)
		return ret;

	while (ret >= 0 && time_is_after_jiffies(end)) {
		ret = s5k6aa_read(client, REG_G_NEW_CFG_SYNC, &reg);
		if (!reg)
			return 0;
		usleep_range(1000, 5000);
	}
	return ret ? ret : -ETIMEDOUT;
}
