calibrate_store(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct elan_tp_data *data = i2c_get_clientdata(client);
	int tries = 20;
	int retval;
	int error;
	u8 val[3];

	retval = mutex_lock_interruptible(&data->sysfs_mutex);
	if (retval)
		return retval;

	disable_irq(client->irq);

	data->mode |= ETP_ENABLE_CALIBRATE;
	retval = data->ops->set_mode(client, data->mode);
	if (retval) {
		dev_err(dev, "failed to enable calibration mode: %d\n",
			retval);
		goto out;
	}

	retval = data->ops->calibrate(client);
	if (retval) {
		dev_err(dev, "failed to start calibration: %d\n",
			retval);
		goto out_disable_calibrate;
	}

	val[0] = 0xff;
	do {

		msleep(250);

		retval = data->ops->calibrate_result(client, val);
		if (retval)
			dev_err(dev, "failed to check calibration result: %d\n",
				retval);
		else if (val[0] == 0)
			break;

	} while (--tries);

	if (tries == 0) {
		dev_err(dev, "failed to calibrate. Timeout.\n");
		retval = -ETIMEDOUT;
	}

out_disable_calibrate:
	data->mode &= ~ETP_ENABLE_CALIBRATE;
	error = data->ops->set_mode(data->client, data->mode);
	if (error) {
		dev_err(dev, "failed to disable calibration mode: %d\n",
			error);
		if (!retval)
			retval = error;
	}
out:
	enable_irq(client->irq);
	mutex_unlock(&data->sysfs_mutex);
	return retval ?: count;
}
