em28xx_pctv_290e_set_lna(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct em28xx_i2c_bus *i2c_bus = fe->dvb->priv;
	struct em28xx *dev = i2c_bus->dev;
#ifdef CONFIG_GPIOLIB
	struct em28xx_dvb *dvb = dev->dvb;
	int ret;
	unsigned long flags;

	if (c->lna == 1)
		flags = GPIOF_OUT_INIT_HIGH;
	else
		flags = GPIOF_OUT_INIT_LOW;

	ret = gpio_request_one(dvb->lna_gpio, flags, NULL);
	if (ret)
		em28xx_errdev("gpio request failed %d\n", ret);
	else
		gpio_free(dvb->lna_gpio);

	return ret;
#else
	dev_warn(&dev->udev->dev, "%s: LNA control is disabled (lna=%u)\n",
		 KBUILD_MODNAME, c->lna);
	return 0;
#endif
}
