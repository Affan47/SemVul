gab_remove(struct platform_device *pdev)
{
	int chan;
	struct gab *adc_bat = platform_get_drvdata(pdev);
	struct gab_platform_data *pdata = adc_bat->pdata;

	power_supply_unregister(adc_bat->psy);

	if (gpio_is_valid(pdata->gpio_charge_finished)) {
		free_irq(gpio_to_irq(pdata->gpio_charge_finished), adc_bat);
		gpio_free(pdata->gpio_charge_finished);
	}

	for (chan = 0; chan < ARRAY_SIZE(gab_chan_name); chan++) {
		if (adc_bat->channel[chan])
			iio_channel_release(adc_bat->channel[chan]);
	}

	kfree(adc_bat->psy_desc.properties);
	cancel_delayed_work(&adc_bat->bat_work);
	return 0;
}
