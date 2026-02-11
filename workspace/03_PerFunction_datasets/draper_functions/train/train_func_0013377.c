ds3232_remove(struct i2c_client *client)
{
	struct ds3232 *ds3232 = i2c_get_clientdata(client);

	if (client->irq > 0) {
		mutex_lock(&ds3232->mutex);
		ds3232->exiting = 1;
		mutex_unlock(&ds3232->mutex);

		devm_free_irq(&client->dev, client->irq, client);
		cancel_work_sync(&ds3232->work);
	}

	return 0;
}
