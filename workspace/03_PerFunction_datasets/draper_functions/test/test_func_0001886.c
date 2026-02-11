tps65090_i2c_remove(struct i2c_client *client)
{
	struct tps65090 *tps65090 = i2c_get_clientdata(client);

	mfd_remove_devices(tps65090->dev);
	if (client->irq)
		regmap_del_irq_chip(client->irq, tps65090->irq_data);

	return 0;
}
