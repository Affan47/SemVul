calibrate_vrtc_work(struct work_struct *work)
{
	struct pm860x_rtc_info *info = container_of(work,
		struct pm860x_rtc_info, calib_work.work);
	unsigned char buf[2];
	unsigned int sum, data, mean, vrtc_set;
	int i;

	for (i = 0, sum = 0; i < 16; i++) {
		msleep(100);
		pm860x_bulk_read(info->i2c, REG_VRTC_MEAS1, 2, buf);
		data = (buf[0] << 4) | buf[1];
		data = (data * 5400) >> 12;
		sum += data;
	}
	mean = sum >> 4;
	vrtc_set = 2700 + (info->vrtc & 0x3) * 200;
	dev_dbg(info->dev, "mean:%d, vrtc_set:%d\n", mean, vrtc_set);

	sum = pm860x_reg_read(info->i2c, PM8607_RTC_MISC1);
	data = sum & 0x3;
	if ((mean + 200) < vrtc_set) {

		if (++data == 4)
			goto out;
		data = (sum & 0xf8) | (data & 0x3);
		pm860x_reg_write(info->i2c, PM8607_RTC_MISC1, data);
	} else if ((mean - 200) > vrtc_set) {

		if (data-- == 0)
			goto out;
		data = (sum & 0xf8) | (data & 0x3);
		pm860x_reg_write(info->i2c, PM8607_RTC_MISC1, data);
	} else
		goto out;
	dev_dbg(info->dev, "set 0x%x to RTC_MISC1\n", data);

	schedule_delayed_work(&info->calib_work, VRTC_CALIB_INTERVAL);
	return;
out:

	pm860x_set_bits(info->i2c, PM8607_MEAS_EN2, MEAS2_VRTC, 0);
	dev_dbg(info->dev, "finish VRTC calibration\n");
	return;
}
