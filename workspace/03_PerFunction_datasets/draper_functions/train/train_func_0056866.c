kempld_i2c_probe(struct platform_device *pdev)
{
	struct kempld_device_data *pld = dev_get_drvdata(pdev->dev.parent);
	struct kempld_i2c_data *i2c;
	int ret;
	u8 ctrl;

	i2c = devm_kzalloc(&pdev->dev, sizeof(*i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	i2c->pld = pld;
	i2c->dev = &pdev->dev;
	i2c->adap = kempld_i2c_adapter;
	i2c->adap.dev.parent = i2c->dev;
	i2c_set_adapdata(&i2c->adap, i2c);
	platform_set_drvdata(pdev, i2c);

	kempld_get_mutex(pld);
	ctrl = kempld_read8(pld, KEMPLD_I2C_CTRL);

	if (ctrl & I2C_CTRL_EN)
		i2c->was_active = true;

	kempld_i2c_device_init(i2c);
	kempld_release_mutex(pld);


	if (i2c_bus >= -1)
		i2c->adap.nr = i2c_bus;
	ret = i2c_add_numbered_adapter(&i2c->adap);
	if (ret)
		return ret;

	dev_info(i2c->dev, "I2C bus initialized at %dkHz\n",
		 bus_frequency);

	return 0;
}
