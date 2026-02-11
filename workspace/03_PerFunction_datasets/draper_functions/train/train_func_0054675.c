htu21_update_measurements(struct device *dev)
{
	struct htu21 *htu21 = dev_get_drvdata(dev);
	struct i2c_client *client = htu21->client;
	int ret = 0;

	mutex_lock(&htu21->lock);

	if (time_after(jiffies, htu21->last_update + HZ / 2) ||
	    !htu21->valid) {
		ret = i2c_smbus_read_word_swapped(client,
						  HTU21_T_MEASUREMENT_HM);
		if (ret < 0)
			goto out;
		htu21->temperature = htu21_temp_ticks_to_millicelsius(ret);
		ret = i2c_smbus_read_word_swapped(client,
						  HTU21_RH_MEASUREMENT_HM);
		if (ret < 0)
			goto out;
		htu21->humidity = htu21_rh_ticks_to_per_cent_mille(ret);
		htu21->last_update = jiffies;
		htu21->valid = true;
	}
out:
	mutex_unlock(&htu21->lock);

	return ret >= 0 ? 0 : ret;
}
