store_in_min(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	int nr = (to_sensor_dev_attr(attr))->index;
	struct lm93_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int vccp = nr - 6;
	long vid;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	if ((nr == 6 || nr == 7) && vccp_limit_type[vccp]) {
		vid = LM93_VID_FROM_REG(data->vid[vccp]);
		data->vccp_limits[vccp] = (data->vccp_limits[vccp] & 0xf0) |
				LM93_IN_REL_TO_REG(val, 0, vid);
		lm93_write_byte(client, LM93_REG_VCCP_LIMIT_OFF(vccp),
				data->vccp_limits[vccp]);
	} else {
		data->block7[nr].min = LM93_IN_TO_REG(nr, val);
		lm93_write_byte(client, LM93_REG_IN_MIN(nr),
				data->block7[nr].min);
	}
	mutex_unlock(&data->update_lock);
	return count;
}
