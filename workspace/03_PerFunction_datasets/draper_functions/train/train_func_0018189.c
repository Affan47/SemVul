ds1374_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct ds1374 *ds1374;
	int ret;

	ds1374 = devm_kzalloc(&client->dev, sizeof(struct ds1374), GFP_KERNEL);
	if (!ds1374)
		return -ENOMEM;

	ds1374->client = client;
	i2c_set_clientdata(client, ds1374);

	INIT_WORK(&ds1374->work, ds1374_work);
	mutex_init(&ds1374->mutex);

	ret = ds1374_check_rtc_status(client);
	if (ret)
		return ret;

	if (client->irq > 0) {
		ret = devm_request_irq(&client->dev, client->irq, ds1374_irq, 0,
					"ds1374", client);
		if (ret) {
			dev_err(&client->dev, "unable to request IRQ\n");
			return ret;
		}

		device_set_wakeup_capable(&client->dev, 1);
	}

	ds1374->rtc = devm_rtc_device_register(&client->dev, client->name,
						&ds1374_rtc_ops, THIS_MODULE);
	if (IS_ERR(ds1374->rtc)) {
		dev_err(&client->dev, "unable to register the class device\n");
		return PTR_ERR(ds1374->rtc);
	}

#ifdef CONFIG_RTC_DRV_DS1374_WDT
	save_client = client;
	ret = misc_register(&ds1374_miscdev);
	if (ret)
		return ret;
	ret = register_reboot_notifier(&ds1374_wdt_notifier);
	if (ret) {
		misc_deregister(&ds1374_miscdev);
		return ret;
	}
	ds1374_wdt_settimeout(131072);
#endif

	return 0;
}
