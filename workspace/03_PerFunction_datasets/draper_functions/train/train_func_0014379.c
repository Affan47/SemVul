cyapa_resume(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct cyapa *cyapa = i2c_get_clientdata(client);
	int error;

	mutex_lock(&cyapa->state_sync_lock);

	if (device_may_wakeup(dev) && cyapa->irq_wake) {
		disable_irq_wake(client->irq);
		cyapa->irq_wake = false;
	}


	error = cyapa_reinitialize(cyapa);
	if (error)
		dev_warn(dev, "failed to reinitialize TP device: %d\n", error);

	enable_irq(client->irq);

	mutex_unlock(&cyapa->state_sync_lock);
	return 0;
}
