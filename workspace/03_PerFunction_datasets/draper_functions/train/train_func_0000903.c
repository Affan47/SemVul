calc_capacity(struct pm860x_battery_info *info, int *cap)
{
	int ret;
	int data;
	int ibat;
	int cap_ocv = 0;
	int cap_cc = 0;

	ret = calc_ccnt(info, &ccnt_data);
	if (ret)
		goto out;
soc:
	data = info->max_capacity * info->start_soc / 100;
	if (ccnt_data.total_dischg - ccnt_data.total_chg <= data) {
		cap_cc =
		    data + ccnt_data.total_chg - ccnt_data.total_dischg;
	} else {
		clear_ccnt(info, &ccnt_data);
		calc_soc(info, OCV_MODE_ACTIVE, &info->start_soc);
		dev_dbg(info->dev, "restart soc = %d !\n",
			info->start_soc);
		goto soc;
	}

	cap_cc = cap_cc * 100 / info->max_capacity;
	if (cap_cc < 0)
		cap_cc = 0;
	else if (cap_cc > 100)
		cap_cc = 100;

	dev_dbg(info->dev, "%s, last cap : %d", __func__,
		info->last_capacity);

	ret = measure_current(info, &ibat);
	if (ret)
		goto out;

	if (ibat < 0) {
		ret = calc_soc(info, OCV_MODE_ACTIVE, &cap_ocv);
		if (ret)
			cap_ocv = info->last_capacity;
		ret = measure_vbatt(info, OCV_MODE_ACTIVE, &data);
		if (ret)
			goto out;
		if (data <= LOW_BAT_THRESHOLD) {


			*cap = min(cap_ocv, cap_cc);
		} else {


			if (cap_cc < 15 && cap_ocv - cap_cc > 10)
				*cap = cap_ocv;
			else
				*cap = cap_cc;
		}


		if (*cap > info->last_capacity)
			*cap = info->last_capacity;
	} else {
		*cap = cap_cc;
	}
	info->last_capacity = *cap;

	dev_dbg(info->dev, "%s, cap_ocv:%d cap_cc:%d, cap:%d\n",
		(ibat < 0) ? "discharging" : "charging",
		 cap_ocv, cap_cc, *cap);


	pm860x_set_bits(info->i2c, PM8607_RTC_MISC2, RTC_SOC_5LSB,
			(*cap & 0x1F) << 3);
	pm860x_set_bits(info->i2c, PM8607_RTC1, RTC_SOC_3MSB,
			((*cap >> 5) & 0x3));
	return 0;
out:
	return ret;
}
