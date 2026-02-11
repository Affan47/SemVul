ds1305_get_alarm(struct device *dev, struct rtc_wkalrm *alm)
{
	struct ds1305	*ds1305 = dev_get_drvdata(dev);
	struct spi_device *spi = ds1305->spi;
	u8		addr;
	int		status;
	u8		buf[DS1305_ALM_LEN];


	addr = DS1305_CONTROL;
	status = spi_write_then_read(spi, &addr, sizeof(addr),
			ds1305->ctrl, sizeof(ds1305->ctrl));
	if (status < 0)
		return status;

	alm->enabled = !!(ds1305->ctrl[0] & DS1305_AEI0);
	alm->pending = !!(ds1305->ctrl[1] & DS1305_AEI0);


	addr = DS1305_ALM0(DS1305_SEC);
	status = spi_write_then_read(spi, &addr, sizeof(addr),
			buf, sizeof(buf));
	if (status < 0)
		return status;

	dev_vdbg(dev, "%s: %02x %02x %02x %02x\n",
		"alm0 read", buf[DS1305_SEC], buf[DS1305_MIN],
		buf[DS1305_HOUR], buf[DS1305_WDAY]);

	if ((DS1305_ALM_DISABLE & buf[DS1305_SEC])
			|| (DS1305_ALM_DISABLE & buf[DS1305_MIN])
			|| (DS1305_ALM_DISABLE & buf[DS1305_HOUR]))
		return -EIO;


	alm->time.tm_sec = bcd2bin(buf[DS1305_SEC]);
	alm->time.tm_min = bcd2bin(buf[DS1305_MIN]);
	alm->time.tm_hour = bcd2hour(buf[DS1305_HOUR]);
	alm->time.tm_mday = -1;
	alm->time.tm_mon = -1;
	alm->time.tm_year = -1;

	alm->time.tm_wday = -1;
	alm->time.tm_mday = -1;
	alm->time.tm_isdst = -1;

	return 0;
}
