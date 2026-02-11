set_fan_div(struct device *dev, struct device_attribute *attr,
	const char *buf, size_t count)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct lm80_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	unsigned long min, val;
	u8 reg;
	int err = kstrtoul(buf, 10, &val);
	if (err < 0)
		return err;


	mutex_lock(&data->update_lock);
	min = FAN_FROM_REG(data->fan[f_min][nr],
			   DIV_FROM_REG(data->fan_div[nr]));

	switch (val) {
	case 1:
		data->fan_div[nr] = 0;
		break;
	case 2:
		data->fan_div[nr] = 1;
		break;
	case 4:
		data->fan_div[nr] = 2;
		break;
	case 8:
		data->fan_div[nr] = 3;
		break;
	default:
		dev_err(dev,
			"fan_div value %ld not supported. Choose one of 1, 2, 4 or 8!\n",
			val);
		mutex_unlock(&data->update_lock);
		return -EINVAL;
	}

	reg = (lm80_read_value(client, LM80_REG_FANDIV) &
	       ~(3 << (2 * (nr + 1)))) | (data->fan_div[nr] << (2 * (nr + 1)));
	lm80_write_value(client, LM80_REG_FANDIV, reg);


	data->fan[f_min][nr] = FAN_TO_REG(min, DIV_FROM_REG(data->fan_div[nr]));
	lm80_write_value(client, LM80_REG_FAN_MIN(nr + 1),
			 data->fan[f_min][nr]);
	mutex_unlock(&data->update_lock);

	return count;
}
