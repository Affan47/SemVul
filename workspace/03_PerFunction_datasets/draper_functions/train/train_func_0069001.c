store_temp_beep(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	struct nct6775_data *data = dev_get_drvdata(dev);
	int nr, bit, regindex;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err < 0)
		return err;
	if (val > 1)
		return -EINVAL;

	nr = find_temp_source(data, sattr->index, data->num_temp_beeps);
	if (nr < 0)
		return nr;

	bit = data->BEEP_BITS[nr + TEMP_ALARM_BASE];
	regindex = bit >> 3;

	mutex_lock(&data->update_lock);
	if (val)
		data->beeps |= (1ULL << bit);
	else
		data->beeps &= ~(1ULL << bit);
	nct6775_write_value(data, data->REG_BEEP[regindex],
			    (data->beeps >> (regindex << 3)) & 0xff);
	mutex_unlock(&data->update_lock);

	return count;
}
