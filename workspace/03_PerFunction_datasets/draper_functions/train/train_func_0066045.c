wm5100_i2c_remove(struct i2c_client *i2c)
{
	struct wm5100_priv *wm5100 = i2c_get_clientdata(i2c);

	snd_soc_unregister_codec(&i2c->dev);
	if (i2c->irq)
		free_irq(i2c->irq, wm5100);
	wm5100_free_gpio(i2c);
	if (wm5100->pdata.reset) {
		gpio_set_value_cansleep(wm5100->pdata.reset, 0);
		gpio_free(wm5100->pdata.reset);
	}
	if (wm5100->pdata.ldo_ena) {
		gpio_set_value_cansleep(wm5100->pdata.ldo_ena, 0);
		gpio_free(wm5100->pdata.ldo_ena);
	}

	return 0;
}
