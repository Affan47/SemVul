max98090_i2c_probe(struct i2c_client *i2c,
				 const struct i2c_device_id *i2c_id)
{
	struct max98090_priv *max98090;
	const struct acpi_device_id *acpi_id;
	kernel_ulong_t driver_data = 0;
	int ret;

	pr_debug("max98090_i2c_probe\n");

	max98090 = devm_kzalloc(&i2c->dev, sizeof(struct max98090_priv),
		GFP_KERNEL);
	if (max98090 == NULL)
		return -ENOMEM;

	if (ACPI_HANDLE(&i2c->dev)) {
		acpi_id = acpi_match_device(i2c->dev.driver->acpi_match_table,
					    &i2c->dev);
		if (!acpi_id) {
			dev_err(&i2c->dev, "No driver data\n");
			return -EINVAL;
		}
		driver_data = acpi_id->driver_data;
	} else if (i2c_id) {
		driver_data = i2c_id->driver_data;
	}

	max98090->devtype = driver_data;
	i2c_set_clientdata(i2c, max98090);
	max98090->pdata = i2c->dev.platform_data;

	ret = of_property_read_u32(i2c->dev.of_node, "maxim,dmic-freq",
				   &max98090->dmic_freq);
	if (ret < 0)
		max98090->dmic_freq = MAX98090_DEFAULT_DMIC_FREQ;

	max98090->regmap = devm_regmap_init_i2c(i2c, &max98090_regmap);
	if (IS_ERR(max98090->regmap)) {
		ret = PTR_ERR(max98090->regmap);
		dev_err(&i2c->dev, "Failed to allocate regmap: %d\n", ret);
		goto err_enable;
	}

	ret = devm_request_threaded_irq(&i2c->dev, i2c->irq, NULL,
		max98090_interrupt, IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
		"max98090_interrupt", max98090);
	if (ret < 0) {
		dev_err(&i2c->dev, "request_irq failed: %d\n",
			ret);
		return ret;
	}

	ret = snd_soc_register_codec(&i2c->dev,
			&soc_codec_dev_max98090, max98090_dai,
			ARRAY_SIZE(max98090_dai));
err_enable:
	return ret;
}
