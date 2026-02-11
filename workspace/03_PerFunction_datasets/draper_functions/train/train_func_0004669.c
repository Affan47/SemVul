smb347_irq_init(struct smb347_charger *smb,
			   struct i2c_client *client)
{
	const struct smb347_charger_platform_data *pdata = smb->pdata;
	int ret, irq = gpio_to_irq(pdata->irq_gpio);

	ret = gpio_request_one(pdata->irq_gpio, GPIOF_IN, client->name);
	if (ret < 0)
		goto fail;

	ret = request_threaded_irq(irq, NULL, smb347_interrupt,
				   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				   client->name, smb);
	if (ret < 0)
		goto fail_gpio;

	ret = smb347_set_writable(smb, true);
	if (ret < 0)
		goto fail_irq;


	ret = regmap_update_bits(smb->regmap, CFG_STAT,
				 CFG_STAT_ACTIVE_HIGH | CFG_STAT_DISABLED,
				 CFG_STAT_DISABLED);
	if (ret < 0)
		goto fail_readonly;

	smb347_set_writable(smb, false);
	client->irq = irq;
	return 0;

fail_readonly:
	smb347_set_writable(smb, false);
fail_irq:
	free_irq(irq, smb);
fail_gpio:
	gpio_free(pdata->irq_gpio);
fail:
	client->irq = 0;
	return ret;
}
