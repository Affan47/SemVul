rv3029c2_rtc_i2c_set_alarm(struct i2c_client *client,
					struct rtc_wkalrm *alarm)
{
	struct rtc_time *const tm = &alarm->time;
	int ret;
	u8 regs[8];


	if (tm->tm_year < 100)
		return -EINVAL;

	ret = rv3029c2_i2c_get_sr(client, regs);
	if (ret < 0) {
		dev_err(&client->dev, "%s: reading SR failed\n", __func__);
		return -EIO;
	}
	regs[RV3029C2_A_SC-RV3029C2_A_SC] = bin2bcd(tm->tm_sec & 0x7f);
	regs[RV3029C2_A_MN-RV3029C2_A_SC] = bin2bcd(tm->tm_min & 0x7f);
	regs[RV3029C2_A_HR-RV3029C2_A_SC] = bin2bcd(tm->tm_hour & 0x3f);
	regs[RV3029C2_A_DT-RV3029C2_A_SC] = bin2bcd(tm->tm_mday & 0x3f);
	regs[RV3029C2_A_MO-RV3029C2_A_SC] = bin2bcd((tm->tm_mon & 0x1f) - 1);
	regs[RV3029C2_A_DW-RV3029C2_A_SC] = bin2bcd((tm->tm_wday & 7) - 1);
	regs[RV3029C2_A_YR-RV3029C2_A_SC] = bin2bcd((tm->tm_year & 0x7f) - 100);

	ret = rv3029c2_i2c_write_regs(client, RV3029C2_A_SC, regs,
					RV3029C2_ALARM_SECTION_LEN);
	if (ret < 0)
		return ret;

	if (alarm->enabled) {
		u8 buf[1];


		ret = rv3029c2_i2c_read_regs(client, RV3029C2_IRQ_FLAGS,
						buf, 1);
		if (ret < 0) {
			dev_err(&client->dev, "can't read alarm flag\n");
			return ret;
		}
		buf[0] &= ~RV3029C2_IRQ_FLAGS_AF;
		ret = rv3029c2_i2c_write_regs(client, RV3029C2_IRQ_FLAGS,
						buf, 1);
		if (ret < 0) {
			dev_err(&client->dev, "can't set alarm flag\n");
			return ret;
		}

		ret = rv3029c2_rtc_i2c_alarm_set_irq(client, 1);
		if (ret)
			return ret;

		dev_dbg(&client->dev, "alarm IRQ armed\n");
	} else {

		ret = rv3029c2_rtc_i2c_alarm_set_irq(client, 0);
		if (ret)
			return ret;

		dev_dbg(&client->dev, "alarm IRQ disabled\n");
	}

	return 0;
}
