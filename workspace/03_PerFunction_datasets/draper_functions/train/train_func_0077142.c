em3027_set_time(struct device *dev, struct rtc_time *tm)
{
	struct i2c_client *client = to_i2c_client(dev);
	unsigned char buf[8];

	struct i2c_msg msg = {
		.addr = client->addr,
		.len = 8,
		.buf = buf,
	};

	buf[0] = EM3027_REG_WATCH_SEC;
	buf[1] = bin2bcd(tm->tm_sec);
	buf[2] = bin2bcd(tm->tm_min);
	buf[3] = bin2bcd(tm->tm_hour);
	buf[4] = bin2bcd(tm->tm_mday);
	buf[5] = bin2bcd(tm->tm_wday);
	buf[6] = bin2bcd(tm->tm_mon);
	buf[7] = bin2bcd(tm->tm_year % 100);


	if ((i2c_transfer(client->adapter, &msg, 1)) != 1) {
		dev_err(&client->dev, "%s: write error\n", __func__);
		return -EIO;
	}

	return 0;
}
