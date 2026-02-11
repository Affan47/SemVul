store_bank1_setting(struct device *dev, struct device_attribute
	*devattr, const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	struct abituguru_data *data = dev_get_drvdata(dev);
	unsigned long val;
	ssize_t ret;

	ret = kstrtoul(buf, 10, &val);
	if (ret)
		return ret;

	ret = count;
	val = (val * 255 + data->bank1_max_value[attr->index] / 2) /
		data->bank1_max_value[attr->index];
	if (val > 255)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	if (data->bank1_settings[attr->index][attr->nr] != val) {
		u8 orig_val = data->bank1_settings[attr->index][attr->nr];
		data->bank1_settings[attr->index][attr->nr] = val;
		if (abituguru_write(data, ABIT_UGURU_SENSOR_BANK1 + 2,
				attr->index, data->bank1_settings[attr->index],
				3) <= attr->nr) {
			data->bank1_settings[attr->index][attr->nr] = orig_val;
			ret = -EIO;
		}
	}
	mutex_unlock(&data->update_lock);
	return ret;
}
