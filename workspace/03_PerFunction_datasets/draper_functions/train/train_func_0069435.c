zforce_suspend(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct zforce_ts *ts = i2c_get_clientdata(client);
	struct input_dev *input = ts->input;
	int ret = 0;

	mutex_lock(&input->mutex);
	ts->suspending = true;


	if (device_may_wakeup(&client->dev)) {
		dev_dbg(&client->dev, "suspend while being a wakeup source\n");


		if (!input->users) {
			ret = zforce_start(ts);
			if (ret)
				goto unlock;
		}

		enable_irq_wake(client->irq);
	} else if (input->users) {
		dev_dbg(&client->dev,
			"suspend without being a wakeup source\n");

		ret = zforce_stop(ts);
		if (ret)
			goto unlock;

		disable_irq(client->irq);
	}

	ts->suspended = true;

unlock:
	ts->suspending = false;
	mutex_unlock(&input->mutex);

	return ret;
}
