set_pwm_auto_temp(struct device *dev,
				 struct device_attribute *devattr,
				 const char *buf,
				 size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct adt7470_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int pwm_auto_reg = ADT7470_REG_PWM_AUTO_TEMP(attr->index);
	long temp;
	u8 reg;

	if (kstrtol(buf, 10, &temp))
		return -EINVAL;

	temp = cvt_auto_temp(temp);
	if (temp < 0)
		return temp;

	mutex_lock(&data->lock);
	data->pwm_automatic[attr->index] = temp;
	reg = i2c_smbus_read_byte_data(client, pwm_auto_reg);

	if (!(attr->index % 2)) {
		reg &= 0xF;
		reg |= (temp << 4) & 0xF0;
	} else {
		reg &= 0xF0;
		reg |= temp & 0xF;
	}

	i2c_smbus_write_byte_data(client, pwm_auto_reg, reg);
	mutex_unlock(&data->lock);

	return count;
}
