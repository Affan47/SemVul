si476x_core_remove(struct i2c_client *client)
{
	struct si476x_core *core = i2c_get_clientdata(client);

	si476x_core_pronounce_dead(core);
	mfd_remove_devices(&client->dev);

	if (client->irq)
		disable_irq(client->irq);
	else
		cancel_delayed_work_sync(&core->status_monitor);

	kfifo_free(&core->rds_fifo);

	if (gpio_is_valid(core->gpio_reset))
		gpio_free(core->gpio_reset);

	return 0;
}
