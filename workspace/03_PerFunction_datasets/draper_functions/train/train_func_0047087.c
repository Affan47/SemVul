rt298_i2c_remove(struct i2c_client *i2c)
{
	struct rt298_priv *rt298 = i2c_get_clientdata(i2c);

	if (i2c->irq)
		free_irq(i2c->irq, rt298);
	snd_soc_unregister_codec(&i2c->dev);

	return 0;
}
