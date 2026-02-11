set_in(struct device *dev, struct device_attribute *attr,
		      const char *buf, size_t count)
{
	struct dme1737_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	int ix = sensor_attr_2->index;
	int fn = sensor_attr_2->nr;
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	switch (fn) {
	case SYS_IN_MIN:
		data->in_min[ix] = IN_TO_REG(val, data->in_nominal[ix]);
		dme1737_write(data, DME1737_REG_IN_MIN(ix),
			      data->in_min[ix]);
		break;
	case SYS_IN_MAX:
		data->in_max[ix] = IN_TO_REG(val, data->in_nominal[ix]);
		dme1737_write(data, DME1737_REG_IN_MAX(ix),
			      data->in_max[ix]);
		break;
	default:
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}
	mutex_unlock(&data->update_lock);

	return count;
}
